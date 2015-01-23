#include "printreport.h"
#include "ui_printreport.h"

PrintReport::PrintReport(QString forn, magazzino::Documenti reportType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintReport)
{
    qDebug() << "PrintReport::PrintReport()";
    ui->setupUi(this);

    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;
    fornitore = forn;
    report = reportType;
    setReport(report);
    setWindowTitle("Stampa");
    ui->lb_info->setText("In attesa di conferma\nCliccare su Stampa per avviare il setup");
}

PrintReport::~PrintReport()
{
    qDebug() << "PrintReport::~PrintReport()";
    delete ui;
    delete printModel;
    delete printer;
    delete painter;
}

void PrintReport::print()
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

        title = QRect(0, 0, pageWidth, magazzino::PRINT_TITLE_HEIGHT);
        const int leftMargin = magazzino::PRINT_MARGINS;
        const int rightMargin = magazzino::PRINT_MARGINS*2;
        col1 = QRect(colWidth*0+leftMargin, 0, (colWidth*1)-rightMargin, magazzino::PRINT_COLS_HEIGHT);
        col2 = QRect(colWidth*1+leftMargin, 0, (colWidth*3)-rightMargin, magazzino::PRINT_COLS_HEIGHT);
        col3 = QRect(colWidth*4+leftMargin, 0, (colWidth*1)-rightMargin, magazzino::PRINT_COLS_HEIGHT);
        col4 = QRect(colWidth*5+leftMargin, 0, (colWidth*1)-rightMargin, magazzino::PRINT_COLS_HEIGHT);

        printHeader(titleStr.arg(1));
        printData(report);
        painter->end();

        ui->lb_info->setText("Stampa eseguita\n"
                             "Avviare nuova stampa o uscire");
    }
}

void PrintReport::setReport(magazzino::Documenti reportType)
{
    qDebug() << "PrintReport::setReport()";

    QString CURRENT_DATE = QDate::currentDate().toString("dd/MM/yyyy");
    QString CURRENT_YEARS = QDate::currentDate().toString("yyyy");
    printModel = new QSqlQueryModel;

    if (reportType == magazzino::LISTINO) {
        titleStr = QString("Listino %1 del %2 pag. %3").arg(fornitore).arg(CURRENT_DATE);
        QString query = magazzino::SELECT_ARTICOLI_FROM_FORN.arg(fornitore);
        printModel->setQuery(query);
        col1Name = settings.value(magazzino::LISTINO_COL1, magazzino::CMP_COD_ART).toString();
        col2Name = settings.value(magazzino::LISTINO_COL2, magazzino::CMP_DESCR).toString();
        col3Name = settings.value(magazzino::LISTINO_COL3, magazzino::CMP_PRZ_ACQ).toString();
        col4Name = settings.value(magazzino::LISTINO_COL4, magazzino::CMP_PRZ_VEN).toString();
    }
    else if (reportType == magazzino::INVENTARIO) {
        titleStr = QString("Inventario %1 pag. %2").arg(CURRENT_YEARS);
        printModel->setQuery(magazzino::SELECT_INVENTARIO);
        col1Name = magazzino::CMP_QT;
        col2Name = magazzino::CMP_DESCR;
        col3Name = magazzino::CMP_PRZ_ACQ;
        col4Name = magazzino::CMP_SUBTOT;
    }
    else if  (reportType == magazzino::ORDINE) {
        titleStr = QString("Ordine %1 del %2 pag.%3").arg(fornitore).arg(CURRENT_DATE);
        QString query = magazzino::SELECT_ORDINE.arg(fornitore);
        printModel->setQuery(query);
        col1Name = settings.value(magazzino::ORDINE_COL1, magazzino::CMP_COD_ART).toString();
        col2Name = settings.value(magazzino::ORDINE_COL2, magazzino::CMP_DESCR).toString();
        col3Name = settings.value(magazzino::ORDINE_COL3, magazzino::CMP_QT).toString();
        col4Name = settings.value(magazzino::ORDINE_COL4, magazzino::CMP_SCORTA).toString();
    }
    else {
        return;
    }
}

void PrintReport::printHeader(QString titleStr)
{
    qDebug() << "PrintReport::printHeader()";
    //Stampo titolo
    painter->drawText(title, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &title);

    //Stampo l'intestazione delle tabelle
    setRow(0);

    painter->drawText(col1, Qt::AlignCenter, col1Name);
    painter->drawText(col2, Qt::AlignCenter, col2Name);
    painter->drawText(col3, Qt::AlignCenter, col3Name);
    painter->drawText(col4, Qt::AlignCenter, col4Name);

    //Stampo la cornice dell'intestazione
    painter->drawLine(0, magazzino::PRINT_TITLE_HEIGHT, pageWidth, magazzino::PRINT_TITLE_HEIGHT);
    painter->drawLine(0, magazzino::PRINT_TITLE_HEIGHT+magazzino::PRINT_COLS_HEIGHT, pageWidth, magazzino::PRINT_TITLE_HEIGHT+magazzino::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, magazzino::PRINT_TITLE_HEIGHT, colWidth*i, magazzino::PRINT_TITLE_HEIGHT+magazzino::PRINT_COLS_HEIGHT );
    }
}

void PrintReport::printRow(int row, QSqlRecord record)
{
    qDebug() << "PrintReport::printRow()";
    setRow(row);

    QString col1Value = record.value(col1Name).toString();
    QString col2Value = record.value(col2Name).toString();
    QString col3Value = record.value(col3Name).toString();
    QString col4Value = record.value(col4Name).toString();

    painter->drawText(col1, Qt::AlignLeft|Qt::AlignVCenter, col1Value);
    painter->drawText(col2, Qt::AlignLeft|Qt::AlignVCenter, col2Value);
    painter->drawText(col3, Qt::AlignRight|Qt::AlignVCenter, col3Value);
    painter->drawText(col4, Qt::AlignRight|Qt::AlignVCenter, col4Value);

    painter->drawLine(0, col1.y()+magazzino::PRINT_COLS_HEIGHT, pageWidth, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, col1.y(), colWidth*i, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    }
}

void PrintReport::printData(magazzino::Documenti reportType)
{
    qDebug() << "PrintReport::printData()";
    const int MAX_ROW = (pageHeight-magazzino::PRINT_TITLE_HEIGHT)/magazzino::PRINT_COLS_HEIGHT;
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
    if (reportType == magazzino::INVENTARIO) {
        printTotale(row+1);
    }

    ui->lb_info->setText("Stampa eseguita\n"
                         "In attesa dell'utente\n");
}

void PrintReport::initPainter()
{
    qDebug() << "PrintReport::initPainter()";
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void PrintReport::setRow(int row)
{
    qDebug() << "PrintReport::setRow()";
    const int y = (row*magazzino::PRINT_COLS_HEIGHT)+magazzino::PRINT_TITLE_HEIGHT;
    col1.moveTop(y);
    col2.moveTop(y);
    col3.moveTop(y);
    col4.moveTop(y);
}

void PrintReport::printTotale(int row)
{
    qDebug() << "PrintReport::printTotale()";
    setRow(row);

    QSqlQuery query(magazzino::SQL_INVENTARIO_TOT);
    query.first();
    QString totale = query.record().value("Totale").toString();
    QString msg = "Totale: %1";

    const int leftMargin = magazzino::PRINT_MARGINS;
    const int rightMargin = magazzino::PRINT_MARGINS*2;
    QRect coltot(colWidth*4+leftMargin, col1.y(), (colWidth*2)-rightMargin, magazzino::PRINT_COLS_HEIGHT);

    painter->drawText(coltot, Qt::AlignRight|Qt::AlignVCenter, msg.arg(totale));
    painter->drawLine(col3.x()-magazzino::PRINT_MARGINS, col1.y()+magazzino::PRINT_COLS_HEIGHT,
                      pageWidth, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*4, col1.y(), colWidth*4, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*6, col1.y(), colWidth*6, col1.y()+magazzino::PRINT_COLS_HEIGHT);
}
