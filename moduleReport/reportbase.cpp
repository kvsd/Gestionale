#include "reportbase.h"

ReportBase::ReportBase(QWidget *parent) :
    QDialog(parent),
    m_printModel(new QSqlQueryModel(this))
{
    qDebug() << "ReportBase::ReportBase() *";

    m_currentDate = QDate::currentDate().toString("dd/MM/yyyy");
    m_currentYears = QDate::currentDate().toString("yyyy");
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

void ReportBase::launchConfigDlg()
{
    qDebug() << "ReportBase::launchConfigDlg() *";
    ConfigPrintDialog dlg(this);
    dlg.exec();
    setReport();
}

void ReportBase::setReport()
{
    qDebug() << "ReportBase::setReport() *";
}
