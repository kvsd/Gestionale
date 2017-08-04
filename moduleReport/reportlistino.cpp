#include "reportlistino.h"
#include "ui_reportlistino.h"

ReportListino::ReportListino(QWidget *parent) :
    ReportBase(parent),
    ui(new Ui::ReportListino),
    m_fornitoreModel(new QSqlQueryModel(this))
{
    qDebug() << "ReportListino::ReportDlg()";
    ui->setupUi(this);

    initComboBox();
    setReport();
}

ReportListino::~ReportListino()
{
    qDebug() << "ReportListino::~PrintReport()";
    delete ui;
}

void ReportListino::initComboBox()
{
    qDebug() << "ReportListino::initComboBox()";
    //Configura il model e il combobox fornitore
    m_fornitoreModel->setQuery(magazzino::SELECT_FORNITORE);
    ui->fornitoreComboBox->blockSignals(true);
    ui->fornitoreComboBox->setModel(m_fornitoreModel);
    ui->fornitoreComboBox->setModelColumn(magazzino::COL_TABLE_DESCRIZIONE);
    ui->fornitoreComboBox->blockSignals(false);
}

void ReportListino::print()
{
    qDebug() << "ReportListino::print()";
    m_printer = new QPrinter(QPrinter::HighResolution);
    QPrintDialog dlg(m_printer, this);
    if (!(dlg.exec() == QPrintDialog::Accepted))
        return;

    m_painter = new QPainter(m_printer);

    Report r(m_painter, m_printer, m_stretchVector, this);
    r.startPrinting();
    r.setPen(Qt::darkBlue);
    r.setFont("fixed", 8); //Creare pannello di configurazione per questa
    r.setTitle(m_titleStr);
    r.setHeaderNames(m_headerName);
    int maxrow = m_printModel->rowCount();
    for (int i=0; i<maxrow; i++) {
        QSqlRecord record = m_printModel->record(i);
        r.print(getFields(record));
    }

    if (maxrow != 0) {
        if (m_printer->outputFileName() != "")
            QDesktopServices::openUrl(QUrl(m_printer->outputFileName()));
        else
            showDialogInfo(this, "info", "Stampa avviata");
    }
    else
        showDialogInfo(this, "Info", "Nulla da stampare");

    delete m_painter;
    delete m_printer;
}

void ReportListino::setReport()
{
    //In base al tipo di report configura il model e le variabili colXName
    qDebug() << "ReportListino::setReport()";
    m_colsName.clear();
    m_stretchVector.clear();
    m_headerName.clear();

    m_titleStr = QString("Listino %1 del %2").arg(m_fornitore, m_currentDate);
    QString query = "";
    if (ui->listinoPrintCurrentDate->isChecked())
        query = report::SELECT_ARTICLE_WITH_CURRENT_DATE.arg(m_fornitore);
    else if (ui->listinoPrintAll->isChecked())
        query = report::SELECT_ALL_ARTICLE_FROM_FORNITORE.arg(m_fornitore);

    m_printModel->setQuery(query);
    m_settings.beginGroup(report::listinoCols);
    for (QString key : m_settings.allKeys()) {
        QStringList values = m_settings.value(key).toStringList();
        m_colsName << values.at(0);
        m_stretchVector << values.at(1).toInt();
        m_headerName << values.at(2);
    }
    m_settings.endGroup();
}

void ReportListino::updateFornitore(QString value)
{
    //Slot collegato a fornitoreComboBox
    qDebug() << "ReportListino::updateFornitore()";
    m_fornitore = value;
    setReport();
}
