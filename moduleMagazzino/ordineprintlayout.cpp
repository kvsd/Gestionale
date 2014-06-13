#include "ordineprintlayout.h"

OrdinePrintLayout::OrdinePrintLayout(QString fornitore, QWidget *parent)
{
    qDebug() << "OrdinePrintLayout()";

    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;

    ordineModel = new QSqlQueryModel;
    QString query = QString::fromUtf8("SELECT * FROM vw_magazzino WHERE \"Quantità\" < \"Scorta Minima\" AND \"Fornitore\" = '%1'");
    ordineModel->setQuery(query.arg(fornitore));

    QPrintDialog printDialog(printer, parent);
    if (printDialog.exec() == QDialog::Accepted) {
        painter->begin(printer);
        initPainter();

        titleStr = titleStr;
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

        col1Name = settings.value(magazzino::ORDINE_COL1, magazzino::CMP_COD_ART).toString();
        col2Name = settings.value(magazzino::ORDINE_COL2, magazzino::CMP_DESCR).toString();
        col3Name = settings.value(magazzino::ORDINE_COL3, magazzino::CMP_QT).toString();
        col4Name = settings.value(magazzino::ORDINE_COL4, magazzino::CMP_SCORTA).toString();

        printHeader(titleStr);
        printData();
        painter->end();
    }
}

OrdinePrintLayout::~OrdinePrintLayout()
{
    qDebug() << "~OrdinePrintLayout()";
    delete printer;
    delete painter;
    delete ordineModel;
}

void OrdinePrintLayout::printHeader(QString titleStr)
{
    qDebug() << "OrdinePrintLayout::printHeader()";
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

void OrdinePrintLayout::printRow(int row, QSqlRecord record)
{
    qDebug() << "OrdinePrintLayout::printRow()";
    setRow(row);

    QString col1Value = record.value(col1Name).toString();
    QString col2Value = record.value(col2Name).toString();
    QString col3Value = record.value(col3Name).toString();
    QString col4Value = record.value(col4Name).toString();

    painter->drawText(col1, Qt::AlignLeft, col1Value);
    painter->drawText(col2, Qt::AlignLeft, col2Value);
    painter->drawText(col3, Qt::AlignRight, col3Value);
    painter->drawText(col4, Qt::AlignRight, col4Value);

    painter->drawLine(0, col1.y()+magazzino::PRINT_COLS_HEIGHT, pageWidth, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, col1.y(), colWidth*i, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    }
}

void OrdinePrintLayout::printData()
{
    qDebug() << "OrdinePrintLayout::printData()";
    int MAX_ROW = (pageHeight-magazzino::PRINT_TITLE_HEIGHT)/magazzino::PRINT_COLS_HEIGHT;
    for (int i=0, row=0; i<ordineModel->rowCount(); i++, row++) {
        if (i%MAX_ROW == 0 && i!=0) {
            printer->newPage();
            row = 0;
            printHeader(titleStr);
        }
        printRow(row+1, ordineModel->record(i));
    }
}

void OrdinePrintLayout::initPainter()
{
    qDebug() << "OrdinePrintLayout::initPainter()";
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void OrdinePrintLayout::setRow(int row)
{
    qDebug() << "OrdinePrintLayout::setRow()";
    const int y = (row*magazzino::PRINT_COLS_HEIGHT)+magazzino::PRINT_TITLE_HEIGHT;
    col1.moveTop(y);
    col2.moveTop(y);
    col3.moveTop(y);
    col4.moveTop(y);
}
