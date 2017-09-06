#include "reportinventario.h"
#include "ui_reportinventario.h"

ReportInventario::ReportInventario(QWidget *parent) :
    ReportBase(parent),
    ui(new Ui::ReportInventario)
{
    qDebug() << "ReportInventario()";
    ui->setupUi(this);
    setReport();
}

ReportInventario::~ReportInventario()
{
    qDebug() << "~ReportInventario()";
    delete ui;
}

QString ReportInventario::getTotale()
{
    qDebug() << "ReportInventario::printTotale()";
    QSqlQuery query(report::SQL_INVENTARIO_TOT);
    if (!query.first())
        return "";
    QString totale = query.value("Totale").toString();
    return totale;
}

void ReportInventario::print()
{
    qDebug() << "ReportInventario::print()";

    setupPrint();

    QVector <Qt::Alignment> v_align = {Align::right, Align::left, Align::right, Align::right};
    int maxrow = m_printModel->rowCount();
    for (int i=0; i<maxrow; i++) {
        QSqlRecord record = m_printModel->record(i);
        m_report->print(getFields(record), v_align);
    }
    QString totale = getTotale();
    if (totale!="") {
        QStringList lastList {"","","Totale", totale};
        m_report->print(lastList, v_align);
    }
    endPrinting(maxrow != 0);
}

void ReportInventario::setReport()
{
    //In base al tipo di report configura il model e le variabili colXName
    qDebug() << "ReportInventario::setReport()";
    m_colsName.clear();
    m_stretchVector.clear();
    m_headerName.clear();

    m_titleStr = (QString("Inventario anno %1").arg(m_currentYears));
    m_printModel->setQuery(report::SELECT_INVENTARIO);
    m_colsName << "Quantità" << "Descrizione" << "Prezzo Acquisto" << "SubTotale";
    m_headerName = m_colsName;
    m_stretchVector << 1 << 3 << 1 << 1;
}
