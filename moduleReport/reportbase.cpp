#include "reportbase.h"

ReportBase::ReportBase(QWidget *parent) :
    QDialog(parent),
    m_printModel(new QSqlQueryModel(this))
{
    qDebug() << "ReportBase::ReportBase() *";

    m_currentDate = QDate::currentDate().toString("dd/MM/yyyy");
    m_currentYears = QDate::currentDate().toString("yyyy");
}

ReportBase::~ReportBase()
{
    qDebug() << "ReportBase::~ReportBase()";
}

QStringList ReportBase::getFields(QSqlRecord &record)
{
    qDebug() << "ReportBase::getFields() *";
    //Metodo che ritorna una QStringList i valori di record. Il nome dei campi
    //viene preso dagli attributi di classe colXName.
    QStringList list;
    for (int col=0; col<m_colsName.length(); col++) {
        list << record.value(m_colsName[col]).toString();
    }
    return list;
}

void ReportBase::setReport()
{
    qDebug() << "ReportBase::setReport() *";
}

void ReportBase::setupPrint()
{
    qDebug() << "ReportBase::setupPrint()";
    m_printer = new QPrinter(QPrinter::HighResolution);
    QPrintDialog dlg(m_printer, this);
    if (!(dlg.exec() == QPrintDialog::Accepted))
        return;

    m_painter = new QPainter(m_printer);

    m_report = new Report(m_painter, m_printer, m_stretchVector, this);
    m_report->startPrinting();
    m_report->setPen(Qt::darkBlue);
    m_report->setFont("fixed", 8); //Creare pannello di configurazione per questa
    m_report->setTitle(m_titleStr);
    m_report->setHeaderNames(m_headerName);
}

void ReportBase::endPrinting(bool status)
{
    qDebug() << "ReportBase::endPrinting()*";
    if (status) {
        if (m_printer->outputFileName() != "")
            QDesktopServices::openUrl(QUrl(m_printer->outputFileName()));
        else
            showDialogInfo(this, "info", "Stampa avviata");
    }
    else
        showDialogInfo(this, "Info", "Nulla da stampare");

    delete m_painter;
    delete m_printer;
    delete m_report;
}
