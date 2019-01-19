#include "documentiwindow.h"
#include "ui_documentiwindow.h"

DocumentiWindow::DocumentiWindow(QWidget *parent) :
    CustomWindow(parent),
    ui(new Ui::DocumentiWindow)
{
    ui->setupUi(this);
    initModel();
    loadConfigSettings();
}

DocumentiWindow::~DocumentiWindow()
{
    delete ui;
}

void DocumentiWindow::loadConfigSettings()
{
    qDebug() << "DocumentiWindow::loadConfigSettings()";
    loadWindowGeometry();
    loadSplittersState();
    //loadTableViewSettings();
}

void DocumentiWindow::saveConfigSettings()
{
    qDebug() << "DocumentiWindow::saveConfigSettings()";
    saveWindowGeometry();
    saveSplittersState();
    //saveTableViewSettings();
}

void DocumentiWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "DocumentiWindow::closeEvent()";
    this->parentWidget()->show();
    saveConfigSettings();
    event->accept();
}

void DocumentiWindow::showEvent(QShowEvent *event)
{
    qDebug() << "DocumentiWindow::showEvent()";
    event->accept();
}

void DocumentiWindow::initModel()
{
    qDebug() << "DocumentiWindow::initModel()";
    m_query = "select doc.id AS \"Id\","
            "       doc.nr_documento AS \"Numero\", "
            "       an.rag_sociale AS \"Rag.Sociale\","
            "       an.nome AS \"Nome\", "
            "       an.cognome AS \"Cognome\" ,"
            "       doc.data AS \"Data\" ,"
            "       doc.importo_tot::numeric::money AS \"Importo\", "
            "       doc.casuale AS \"Casuale\" "
            "FROM documenti AS doc, anagrafica AS an "
            "WHERE doc.id_cliente=an.id "
            "ORDER BY doc.data";
    m_docModel = new CustomModel(this);
    m_docModel->setQuery(m_query);
    ui->documentiView->setModel(m_docModel);
    ui->documentiView->resizeColumnsToContents();

    m_detModel = new CustomModel(this);
    ui->dettaglioView->setModel(m_detModel);
}

void DocumentiWindow::addFattura()
{
    qDebug() << "DocumentiWindow::addFattura()";
    DocumentiAddDialog dlg(this);
    dlg.initFattura();
    bool ok = dlg.exec();
    if (!ok)
        return;
    m_docModel->setQuery(m_query);
    ui->documentiView->resizeColumnsToContents();
}

void DocumentiWindow::removeRecord()
{
    qDebug() << "DocumentiWindow::removeRecord()";
    QModelIndex index = ui->documentiView->currentIndex();
    if (!index.isValid()) {
        qDebug() << "Errore";
        return;
    }

    QString id = m_docModel->record(index.row()).value(coldb::ID).toString();
    QSqlQuery query;
    query.prepare("DELETE FROM documenti WHERE id=:id");
    query.bindValue(ph::ID, id);
    if (!query.exec())
        qDebug() << query.lastError().text();

    m_docModel->setQuery(m_query);
    m_detModel->setQuery("");

}

void DocumentiWindow::updateDettaglio(QModelIndex index)
{
    qDebug() << "DocumentiWindow::updateDettaglio()";
    QString id = m_docModel->record(index.row()).value("id").toString();
    qDebug() << id;
    QString query = "SELECT cod_articolo AS \"Cod.Articolo\", "
                    "       descr AS \"Descrizione\", "
                    "       quantita AS \"Quantità\", "
                    "       um AS \"U.M.\", "
                    "       prezzo_unitario::money AS \"Prezzo Unitario\", "
                    "       prezzo_totale::money AS \"Prezzo Totale\", "
                    "       aliquota_iva AS \"Aliquota IVA\", "
                    "       rif AS \"Riferimento Amm.\" "
                    "FROM documenti_det "
                    "WHERE id_documento=%1 "
                    "ORDER BY linea";
    m_detModel->setQuery(query.arg(id));
    ui->dettaglioView->resizeColumnsToContents();
    ui->dettaglioView->horizontalHeader()->setStretchLastSection(true);
}
