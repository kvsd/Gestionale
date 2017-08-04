#include "reportinventario.h"
#include "ui_reportinventario.h"

ReportInventario::ReportInventario(QWidget *parent) :
    ReportBase(parent),
    ui(new Ui::ReportInventario)
{
    ui->setupUi(this);
}

ReportInventario::~ReportInventario()
{
    delete ui;
}

void ReportInventario::print()
{
    qDebug() << "ReportDlg::print()";
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

void ReportInventario::setReport()
{
    //In base al tipo di report configura il model e le variabili colXName
    qDebug() << "ReportDlg::setReport()";
    m_colsName.clear();
    m_stretchVector.clear();
    m_headerName.clear();

    m_titleStr = (QString("Inventario anno %1").arg(m_currentYears));
    m_printModel->setQuery(report::SELECT_INVENTARIO);
    m_colsName << "Quantità" << "Descrizione" << "Prezzo Acquisto" << "SubTotale";
    m_headerName = m_colsName;
    m_stretchVector << 1 << 3 << 1 << 1;
}
