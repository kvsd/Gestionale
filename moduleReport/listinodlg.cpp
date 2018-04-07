#include "listinodlg.h"
#include "ui_listinodlg.h"

ListinoDlg::ListinoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListinoDlg)
{
    qDebug() << "ListinoDlg::ListinoDlg()";
    ui->setupUi(this);
    m_printer = new QPrinter(QPrinter::HighResolution);
    QMargins margin(3.53, 3.53, 3.53, 3.53);
    m_printer->setPageMargins(margin, QPageLayout::Millimeter);
    m_printer->setOutputFileName("./listino.pdf");
    initFornitoreCb();
    configLayout();
}

ListinoDlg::~ListinoDlg()
{
    qDebug() << "ListinoDlg::~ListinoDlg()";
    delete ui;
    delete m_printer;
}

void ListinoDlg::initFornitoreCb()
{
    qDebug() << "ListinoDlg::initFornitoreCb()";
    m_modelFornitori = new QSqlQueryModel(this);
    m_modelFornitori->setQuery(magazzino::SELECT_CB_FORNITORE);
    ui->fornitoreCb->setModel(m_modelFornitori);
    ui->fornitoreCb->setModelColumn(DESCR);
}

void ListinoDlg::configLayout()
{
    qDebug() << "ListinoDlg::getColsLayout()";
    m_colsName.clear();
    m_stretchValues.clear();
    m_viewName.clear();
    m_settings.beginGroup(report::listinoCols);
    for (auto s : m_settings.allKeys()) {
         QStringList value = m_settings.value(s).toStringList();
         m_colsName.append(value.at(ConfigPrintDialog::DESCR));
         m_stretchValues.append(value.at(ConfigPrintDialog::STRETCH).toInt());
         m_viewName.append(value.at(ConfigPrintDialog::VIEW));
         QString alignment = value.at(ConfigPrintDialog::ALIGN);
         if (alignment == align::left)
             m_align.append(Qt::AlignLeft);
         else if (alignment == align::right)
             m_align.append(Qt::AlignRight);
         else
             m_align.append(Qt::AlignHCenter);
    }
    m_settings.endGroup();
    listinoFont.fromString(m_settings.value(report::listinoFont, "fixed").toString());
}

QString ListinoDlg::configQuery(QString fornitore)
{
    qDebug() << "ListinoDlg::configQuery()";
    //Selezione e configurazione delle query
    QString query;
    if (ui->printAllRb->isChecked())
        query = QString(magazzino::SELECT_ARTICOLI_ALL+
                        report::FILTER_FORNITORE).arg(fornitore);
    else if (ui->printFromDateRb->isChecked())
        query = QString(magazzino::SELECT_ARTICOLI_ALL+
                        report::FILTER_CURRENT_DATE).arg(fornitore);
    else if (ui->printFromFatturaRb->isChecked()) {
        QString fattura = ui->fatturaLE->text();
        query = QString(report::SELECT_LISTINO_FATTURA.arg(fornitore, fattura));
    }

    return query;
}

void ListinoDlg::draw()
{
    qDebug() << "ListinoDlg::draw()";
    m_painter = new QPainter(m_printer);
    QString fornitore = ui->fornitoreCb->currentText();
    QString data = QDate::currentDate().toString("dd/MM/yyyy");
    QString title = QString("Listino di %1 del %2").arg(fornitore, data);
    QString query = configQuery(fornitore);

    QueryReport *report = new QueryReport(m_printer, m_painter, this);
    report->setTitle(title);
    report->setTitleBgColor(Qt::gray);
    QFont titleFont = listinoFont;
    titleFont.setPointSize(listinoFont.pointSize()+4);
    report->setTitleFont(titleFont);
    report->setHeaderFont(listinoFont);
    report->setRowFont(listinoFont);
    report->setStretchValues(m_stretchValues);
    report->setQuery(query);
    report->setQueryCols(m_colsName);
    report->setHeaderNames(m_viewName);
    report->setAlignCols(m_align);
    report->draw();

    delete m_painter;
    int size = report->getQuerySize();
    if (size == -1)
        showDialogInfo(this, "Stampa", QString("Si è verificato un errore"));
    else {
        QString title = QString("Articoli stampati: %1").arg(size);
        showDialogInfo(this, "Stampa", title);
    }
}

void ListinoDlg::config()
{
    qDebug() << "ListinoDlg::config()";
    QPrintDialog dlg(m_printer, this);
    if (dlg.exec() == dlg.Accepted)
        draw();
}
