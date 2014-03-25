#include "listinoprintlayout.h"

ListinoPrintLayout::ListinoPrintLayout(CustomModel *model, QString titleStr)
{
    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;

    articoloModel = model;

    titleStr = titleStr;
    titleHeight = 500;
    colHeight = 300;
    margin = 50;
    pageHeight = printer->height();
    pageWidth = printer->width();
    colWidth = pageWidth/6;

    title = QRect(0, 0, pageWidth, titleHeight);
    col1 = QRect(colWidth*0+margin, 0, (colWidth*1)-margin*2, colHeight);
    col2 = QRect(colWidth*1+margin, 0, (colWidth*3)-margin*2, colHeight);
    col3 = QRect(colWidth*4+margin, 0, (colWidth*1)-margin*2, colHeight);
    col4 = QRect(colWidth*5+margin, 0, (colWidth*1)-margin*2, colHeight);

    printer->setOutputFileName("/home/kvsd/print.pdf");
    painter->begin(printer);
    initPainter();

    printHeader(titleStr);
    printData();

    painter->end();
}

ListinoPrintLayout::~ListinoPrintLayout()
{
    delete printer;
    delete painter;
}

void ListinoPrintLayout::printHeader(QString titleStr)
{
    //Stampo titolo
    painter->drawText(title, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &title);

    //Stampo l'intestazione delle tabelle
    setRow(0);
    painter->drawText(col1, Qt::AlignCenter, "Cod.Articolo");
    painter->drawText(col2, Qt::AlignCenter, "Descrizione");
    painter->drawText(col3, Qt::AlignCenter, "Imponibile");
    painter->drawText(col4, Qt::AlignCenter, QString::fromUtf8("Prezzo Vendità"));

    //Stampo la cornice dell'intestazione
    painter->drawLine(0, titleHeight, pageWidth, titleHeight);
    painter->drawLine(0, titleHeight+colHeight, pageWidth, titleHeight+colHeight);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, titleHeight, colWidth*i, titleHeight+colHeight );
    }
}

void ListinoPrintLayout::printRow(int row, QSqlRecord record)
{
    setRow(row);

    QString codarticolo = record.value("Cod.Articolo").toString();
    QString descrizione = record.value("Descrizione").toString();
    QString imponibile  = record.value("Imponibile").toString();
    QString prezzo      = record.value(QString::fromUtf8("Prezzo Vendità")).toString();

    painter->drawText(col1, Qt::AlignLeft, codarticolo);
    painter->drawText(col2, Qt::AlignLeft, descrizione);
    painter->drawText(col3, Qt::AlignRight, imponibile);
    painter->drawText(col4, Qt::AlignRight, prezzo);

    painter->drawLine(0, col1.y()+colHeight, pageWidth, col1.y()+colHeight);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, col1.y(), colWidth*i, col1.y()+colHeight);
    }
}

void ListinoPrintLayout::printData()
{
    for (int i=0, r=0; i<articoloModel->rowCount(); i++, r++) {
        if (i%42 == 0 && i!=0) {
            printer->newPage();
            r = 0;
            printHeader(titleStr);
        }
        printRow(r+1, articoloModel->record(i));
    }
}

void ListinoPrintLayout::initPainter()
{
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void ListinoPrintLayout::setRow(int row)
{
    col1.moveTop(row*colHeight+titleHeight);
    col2.moveTop(row*colHeight+titleHeight);
    col3.moveTop(row*colHeight+titleHeight);
    col4.moveTop(row*colHeight+titleHeight);
}
