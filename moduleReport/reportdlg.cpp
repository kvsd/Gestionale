#include "reportdlg.h"
#include "ui_reportdlg.h"

ReportDlg::ReportDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDlg)
{
    qDebug() << "ReportDlg::PrintReport()";
    ui->setupUi(this);

    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;
    printModel = new QSqlQueryModel(this);

    fornitore = "";
    report = report::LISTINO;
    setReport(report);
    ui->lb_info->setText("In attesa di conferma\nCliccare su Stampa per avviare il setup");
}

ReportDlg::~ReportDlg()
{
    qDebug() << "ReportDlg::~PrintReport()";
    delete ui;
    delete printer;
    delete painter;
}

void ReportDlg::print()
{
    ui->lb_info->setText("In attesa...");

    QPrintDialog printDialog(printer, this);
    printDialog.setWindowTitle("Impostazioni di stampa");
    if (printDialog.exec() == QDialog::Accepted) {
        painter->begin(printer);
        initPainter();

        pageHeight = printer->height();
        pageWidth = printer->width();
        colWidth = pageWidth/6;

        title = QRect(0, 0, pageWidth, report::PRINT_TITLE_HEIGHT);
        const int leftMargin = report::PRINT_MARGINS;
        const int rightMargin = report::PRINT_MARGINS*2;
        col1 = QRect(colWidth*0+leftMargin, 0, (colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);
        col2 = QRect(colWidth*1+leftMargin, 0, (colWidth*3)-rightMargin, report::PRINT_COLS_HEIGHT);
        col3 = QRect(colWidth*4+leftMargin, 0, (colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);
        col4 = QRect(colWidth*5+leftMargin, 0, (colWidth*1)-rightMargin, report::PRINT_COLS_HEIGHT);

        printHeader(titleStr.arg(1));
        printData(report);
        painter->end();

        ui->lb_info->setText("Stampa eseguita\n"
                             "Avviare nuova stampa o uscire");
    }
}

void ReportDlg::setReport(report::Documenti reportType)
{
    qDebug() << "ReportDlg::setReport()";

    QString CURRENT_DATE = QDate::currentDate().toString("dd/MM/yyyy");
    QString CURRENT_YEARS = QDate::currentDate().toString("yyyy");

    if (reportType == report::LISTINO) {
        titleStr = QString("Listino %1 del %2 pag. %3").arg(fornitore).arg(CURRENT_DATE);
        col1Name = settings.value(report::LISTINO_COL1, report::CMP_COD_ART).toString();
        col2Name = settings.value(report::LISTINO_COL2, report::CMP_DESCR).toString();
        col3Name = settings.value(report::LISTINO_COL3, report::CMP_PRZ_ACQ).toString();
        col4Name = settings.value(report::LISTINO_COL4, report::CMP_PRZ_VEN).toString();
    }
    else if (reportType == report::INVENTARIO) {
        titleStr = QString("Inventario %1 pag. %2").arg(CURRENT_YEARS);
        printModel->setQuery(report::SELECT_INVENTARIO);
        col1Name = report::CMP_QT;
        col2Name = report::CMP_DESCR;
        col3Name = report::CMP_PRZ_ACQ;
        col4Name = report::CMP_SUBTOT;
    }
    else if  (reportType == report::ORDINE) {
        titleStr = QString("Ordine %1 del %2 pag.%3").arg(fornitore).arg(CURRENT_DATE);
        QString query = report::SELECT_ORDINE.arg(fornitore);
        printModel->setQuery(query);
        col1Name = settings.value(report::ORDINE_COL1, report::CMP_COD_ART).toString();
        col2Name = settings.value(report::ORDINE_COL2, report::CMP_DESCR).toString();
        col3Name = settings.value(report::ORDINE_COL3, report::CMP_QT).toString();
        col4Name = settings.value(report::ORDINE_COL4, report::CMP_SCORTA).toString();
    }
    else {
        return;
    }
}

void ReportDlg::printHeader(QString titleStr)
{
    qDebug() << "ReportDlg::printHeader()";
    //Stampo titolo
    painter->drawText(title, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &title);

    //Stampo l'intestazione delle tabelle
    setRow(0);

    painter->drawText(col1, Qt::AlignCenter, col1Name);
    painter->drawText(col2, Qt::AlignCenter, col2Name);
    painter->drawText(col3, Qt::AlignCenter, col3Name);
    painter->drawText(col4, Qt::AlignCenter, col4Name);

    //Stampo la cornice dell'intestazione
    painter->drawLine(0, report::PRINT_TITLE_HEIGHT, pageWidth, report::PRINT_TITLE_HEIGHT);
    painter->drawLine(0, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT, pageWidth, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, report::PRINT_TITLE_HEIGHT, colWidth*i, report::PRINT_TITLE_HEIGHT+report::PRINT_COLS_HEIGHT );
    }
}

void ReportDlg::printRow(int row, QSqlRecord record)
{
    qDebug() << "ReportDlg::printRow()";
    setRow(row);

    QString col1Value = record.value(col1Name).toString();
    QString col2Value = record.value(col2Name).toString();
    QString col3Value = record.value(col3Name).toString();
    QString col4Value = record.value(col4Name).toString();

    painter->drawText(col1, Qt::AlignLeft|Qt::AlignVCenter, col1Value);
    painter->drawText(col2, Qt::AlignLeft|Qt::AlignVCenter, col2Value);
    painter->drawText(col3, Qt::AlignRight|Qt::AlignVCenter, col3Value);
    painter->drawText(col4, Qt::AlignRight|Qt::AlignVCenter, col4Value);

    painter->drawLine(0, col1.y()+report::PRINT_COLS_HEIGHT, pageWidth, col1.y()+report::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, col1.y(), colWidth*i, col1.y()+report::PRINT_COLS_HEIGHT);
    }
}

void ReportDlg::printData(report::Documenti reportType)
{
    qDebug() << "ReportDlg::printData()";
    const int MAX_ROW = (pageHeight-report::PRINT_TITLE_HEIGHT)/report::PRINT_COLS_HEIGHT;
    const int ROWS = printModel->rowCount();
    ui->progressBar->setRange(0, ROWS);
    int row = 0;
    int page = 2;
    for (int i=0; i<ROWS; i++, row++) {
        if (i%MAX_ROW == 0 && i!=0) {
            printer->newPage();
            row = 0;
            printHeader(titleStr.arg(page++));
        }
        printRow(row+1, printModel->record(i));
        ui->progressBar->setValue(i+1);
    }
    if (reportType == report::INVENTARIO) {
        printTotale(row+1);
    }

    ui->lb_info->setText("Stampa eseguita\n"
                         "In attesa dell'utente\n");
}

void ReportDlg::initPainter()
{
    qDebug() << "ReportDlg::initPainter()";
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void ReportDlg::setRow(int row)
{
    qDebug() << "ReportDlg::setRow()";
    const int y = (row*report::PRINT_COLS_HEIGHT)+report::PRINT_TITLE_HEIGHT;
    col1.moveTop(y);
    col2.moveTop(y);
    col3.moveTop(y);
    col4.moveTop(y);
}

void ReportDlg::printTotale(int row)
{
    qDebug() << "ReportDlg::printTotale()";
    setRow(row);

    QSqlQuery query(report::SQL_INVENTARIO_TOT);
    query.first();
    QString totale = query.record().value("Totale").toString();
    QString msg = "Totale: %1";

    const int leftMargin = report::PRINT_MARGINS;
    const int rightMargin = report::PRINT_MARGINS*2;
    QRect coltot(colWidth*4+leftMargin, col1.y(), (colWidth*2)-rightMargin, report::PRINT_COLS_HEIGHT);

    painter->drawText(coltot, Qt::AlignRight|Qt::AlignVCenter, msg.arg(totale));
    painter->drawLine(col3.x()-report::PRINT_MARGINS, col1.y()+report::PRINT_COLS_HEIGHT,
                      pageWidth, col1.y()+report::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*4, col1.y(), colWidth*4, col1.y()+report::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*6, col1.y(), colWidth*6, col1.y()+report::PRINT_COLS_HEIGHT);
}
