#include "listinoprintlayout.h"

ListinoPrintLayout::ListinoPrintLayout(CustomModel *model, QString titleStr, QWidget *parent)
{
    qDebug() << "ListinoPrintLayout()";
    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;

    articoloModel = model;

    QPrintDialog printDialog(printer, parent);
    if (printDialog.exec() == QDialog::Accepted) {
        painter->begin(printer);
        initPainter();

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

        printHeader(titleStr);
        printData();
        painter->end();
    }
}

ListinoPrintLayout::~ListinoPrintLayout()
{
    qDebug() << "~ListinoPrintLayout()";
    delete printer;
    delete painter;
}

void ListinoPrintLayout::printHeader(QString titleStr)
{
    qDebug() << "ListinoPrintLayout::printHeader()";
    //Stampo titolo
    painter->drawText(title, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &title);

    //Stampo l'intestazione delle tabelle
    setRow(0);
    painter->drawText(col1, Qt::AlignCenter, magazzino::CMP_COD_ART);
    painter->drawText(col2, Qt::AlignCenter, magazzino::CMP_DESCR);
    painter->drawText(col3, Qt::AlignCenter, magazzino::CMP_PRZ_ACQ);
    painter->drawText(col4, Qt::AlignCenter, magazzino::CMP_PRZ_VEN);

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
    qDebug() << "ListinoPrintLayout::printRow()";
    setRow(row);

    QString codarticolo = record.value(magazzino::CMP_COD_ART).toString();
    QString descrizione = record.value(magazzino::CMP_DESCR).toString();
    QString imponibile  = record.value(magazzino::CMP_PRZ_ACQ).toString();
    QString prezzo      = record.value(magazzino::CMP_PRZ_VEN).toString();

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
    qDebug() << "ListinoPrintLayout::printData()";
    int MAX_ROW = (pageHeight-titleHeight)/colHeight;
    for (int i=0, r=0; i<articoloModel->rowCount(); i++, r++) {
        if (i%MAX_ROW == 0 && i!=0) {
            printer->newPage();
            r = 0;
            printHeader(titleStr);
        }
        printRow(r+1, articoloModel->record(i));
    }
}

void ListinoPrintLayout::initPainter()
{
    qDebug() << "ListinoPrintLayout::initPainter()";
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void ListinoPrintLayout::setRow(int row)
{
    qDebug() << "ListinoPrintLayout::setRow()";
    col1.moveTop(row*colHeight+titleHeight);
    col2.moveTop(row*colHeight+titleHeight);
    col3.moveTop(row*colHeight+titleHeight);
    col4.moveTop(row*colHeight+titleHeight);
}