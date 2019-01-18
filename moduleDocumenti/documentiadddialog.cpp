#include "documentiadddialog.h"
#include "ui_documentiadddialog.h"

DocumentiAddDialog::DocumentiAddDialog(QWidget *parent) :
    CustomInsertDialog(parent),
    ui(new Ui::DocumentiAddDialog)
{
    ui->setupUi(this);

    //La data corrente. Da definire l'ultima data disponibile.
    ui->dateLE->setDate(QDate::currentDate());

    initForm();
    initComboBox();

    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)),
            this, SLOT(updateCell(int,int)));
    connect(ui->tableWidget, SIGNAL(cbTextChanged(int,int,QString)),
            this, SLOT(updateIvaMap()));
    connect(ui->tableWidget, SIGNAL(removedRow()), this, SLOT(updateIvaMap()));
}

DocumentiAddDialog::~DocumentiAddDialog()
{
    delete ui;
}

void DocumentiAddDialog::initFattura()
{
    qDebug() << "DocumentiAddDialog::initFattura()";
    setWindowTitle("Crea Fattura");
    ui->monetaCB->setCurrentText("Euro");
    ui->tipoDocumentoCB->setCurrentText("fattura");
    ui->tableWidget->initFattura();
    //Calcolo la dimensione delle colonne e imposto la dimensione del dialog
    int w=0;
    for (int c=0; c<ui->tableWidget->columnCount(); c++) {
        w += ui->tableWidget->columnWidth(c);
    }
    resize(w+50, height());
}

void DocumentiAddDialog::initDdt()
{
    qDebug() << "DocumentiAddDialog::initDdt()";
    ui->monetaCB->setVisible(false);
    setWindowTitle("Crea DDT");
}

void DocumentiAddDialog::initForm()
{
    qDebug() << "DocumentiAddDialog::initForm()";
    ui->dateLE->setProperty(m_property, coldb::DATA);
    ui->clienteCB->setProperty(m_property, "id_cliente");
    ui->tipoDocumentoCB->setProperty(m_property, "id_tipo_documento");
    ui->monetaCB->setProperty(m_property, "id_moneta");
    ui->casualeLE->setProperty(m_property, "casuale");
}

void DocumentiAddDialog::initComboBox()
{
    qDebug() << "DocumentiAddDialog::initComboBox()";
    m_modelCliente = new QSqlQueryModel(this);
    m_modelCliente->setQuery(documenti::SELECT_CLIENTE);
    ui->clienteCB->setModel(m_modelCliente);
    ui->clienteCB->setModelColumn(1);

    m_modelDocumento = setupComboBox(table::TIPO_DOCUMENTO,
                                     ui->tipoDocumentoCB,
                                     int(modelCols::descr));
    m_modelMoneta = setupComboBox(table::MONETA, ui->monetaCB,
                                  int(modelCols::descr));
}

void DocumentiAddDialog::setValue(QString id)
{
    qDebug() << "DocumentiAddDialog::setValue(QString id)";
}

void DocumentiAddDialog::save()
{
    qDebug() << "DocumentiAddDialog::save()";
    //Documenti
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << db.transaction();
    prepareMap(m_docMap, int(modelCols::id));
    m_docMap[":years"] = ui->dateLE->date().toString("yyyy");

    QSqlQuery query_doc;
    query_doc.prepare(documenti::INSERT_DOC);
    for (QString key : m_docMap.keys())
        query_doc.bindValue(key, m_docMap[key]);

    if (!query_doc.exec()) {
        showDialogError(this, "Errore", query_doc.lastError().text());
        db.rollback();
    }
    //Recupero id documento appena inserito.
    query_doc.first();
    QString id_doc = query_doc.value("id").toString();

    //Documenti dettaglio
    for (int row=0; row<ui->tableWidget->rowCount(); row++) {
        auto map = ui->tableWidget->getRowMap(row);
        if (map[":descr"].isEmpty())
            continue;
        map[":id_documento"] = id_doc;
        map[":linea"] = QString::number(row);
        QSqlQuery query;
        query.prepare(documenti::INSERT_DET);
        for (auto key : map.keys())
            query.bindValue(key, map[key]);
        if (!query.exec()) {
            showDialogError(this, "ERRORE", query.lastError().text());
            db.rollback();
        }
    }

    //Documenti iva
    for (auto key : m_ivaMap.keys()) {
        QSqlQuery query;
        query.prepare(documenti::INSERT_IVA);
        query.bindValue(":id_documento", id_doc);
        double iva = stringToDouble(key);
        query.bindValue(":aliquota_iva", iva);
        query.bindValue(":imponibile", m_ivaMap[key]);
        query.bindValue(":imposta", iva*m_ivaMap[key]/100);
        if (!query.exec()) {
            showDialogError(this, "ERRORE", query.lastError().text());
            db.rollback();
        }
    }

    showDialogInfo(this, "Info", db.commit() ? "La fattura è stata inserita" :
                                               "Si è verificato un problema");
    this->accept();
}

void DocumentiAddDialog::updateCell(int row, int col)
{
    qDebug() << "DocumentiAddDialog::updateCell()";
    if (col == int(CustomTableWidget::cols::qt) ||
            col == int(CustomTableWidget::cols::prezzo_u)) {
        auto item_qt = ui->tableWidget->item(row, int(CustomTableWidget::cols::qt));
        auto item_pu = ui->tableWidget->item(row, int(CustomTableWidget::cols::prezzo_u));
        double qt = stringToDouble(item_qt->text());
        double prezzo_u = stringToDouble(item_pu->text());

        item_qt->setText(QString::number(qt, 'f', 2));
        item_pu->setText(QString::number(prezzo_u, 'f', 2));

        auto item_pt = ui->tableWidget->item(row, int(CustomTableWidget::cols::prezzo_t));
        item_pt->setText(QString::number(qt*prezzo_u, 'f', 2));
        updateIvaMap();
    }
}

void DocumentiAddDialog::updateIvaMap()
{
    qDebug() << "DocumentiAddDialog::getIvaMap()";
    int colPrezzo = int(CustomTableWidget::cols::prezzo_t);
    int colIva = int(CustomTableWidget::cols::al_iva);
    m_ivaMap.clear();

    for (int row=0; row<ui->tableWidget->rowCount(); row++) {
        auto imponibileItem = ui->tableWidget->item(row, colPrezzo);
        auto *cb_iva = qobject_cast<QComboBox *>
                (ui->tableWidget->cellWidget(row, colIva));
        m_ivaMap[cb_iva->currentText()] += stringToDouble(imponibileItem->text());
    }

    double imposta = 0;
    double imponibile = 0;
    for (QString key : m_ivaMap.keys()) {
        imponibile += m_ivaMap[key];
        imposta += m_ivaMap[key]*stringToDouble(key)/100.0;
    }
    m_docMap[":importo_tot"] = QString::number(imponibile+imposta);

    ui->imponibile_LB->setText(locale().toCurrencyString(imponibile));
    ui->imposta_LB->setText(locale().toCurrencyString(imposta));
    ui->totale_LB->setText(locale().toCurrencyString(imponibile+imposta));
}

void DocumentiAddDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "sto chiudendo";
    bool y = showDialogWarning(this, "Chiusura", "Vuoi veramente chiudere?");
    if (y)
        event->accept();
}

void DocumentiAddDialog::reject()
{
    qDebug() << "sto chiudendo";
    bool y = showDialogWarning(this, "Chiusura", "Vuoi veramente chiudere?");
    if (y)
        QDialog::reject();
}
