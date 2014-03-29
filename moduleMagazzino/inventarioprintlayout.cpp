#include "inventarioprintlayout.h"

InventarioPrintLayout::InventarioPrintLayout(QWidget *parent)
{
    const QString INVENTARIO_ROW = QString::fromUtf8("SELECT \"Quantità\", \"Descrizione\", \"Imponibile\", \"Quantità\"*\"Imponibile\" As \"SubTotale\" FROM vw_magazzino WHERE \"Quantità\"!=0 ORDER BY \"Descrizione\" ");

    articoloModel = new QSqlQueryModel;
    articoloModel->setQuery(INVENTARIO_ROW);

    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;

    QPrintDialog printDialog(printer, parent);
    if (printDialog.exec() == QDialog::Accepted) {
        painter->begin(printer);
        initPainter();

        titleStr = QString("%1 Inventario anno %2 pag.%3").arg("Fer.Ba.snc", QDate::currentDate().toString("yyyy"));
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

        printHeader(titleStr.arg(1));
        printData();
        painter->end();
    }    
}


InventarioPrintLayout::~InventarioPrintLayout()
{
    delete articoloModel;
    delete printer;
    delete painter;
}

void InventarioPrintLayout::printHeader(QString titleStr)
{
    //Stampo titolo
    painter->drawText(title, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &title);

    //Stampo l'intestazione delle tabelle
    setRow(0);
    painter->drawText(col1, Qt::AlignCenter, QString::fromUtf8("Quantità"));
    painter->drawText(col2, Qt::AlignCenter, "Descrizione");
    painter->drawText(col3, Qt::AlignCenter, "Imponibile");
    painter->drawText(col4, Qt::AlignCenter, "SubTotale");

    //Stampo la cornice dell'intestazione
    painter->drawLine(0, titleHeight, pageWidth, titleHeight);
    painter->drawLine(0, titleHeight+colHeight, pageWidth, titleHeight+colHeight);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, titleHeight, colWidth*i, titleHeight+colHeight);
    }
}

void InventarioPrintLayout::printRow(int row, QSqlRecord record)
{
    setRow(row);

    QString quantita    = record.value(QString::fromUtf8("Quantità")).toString();
    QString descrizione = record.value("Descrizione").toString();
    QString imponibile  = record.value("Imponibile").toString();
    QString subtotale   = record.value("SubTotale").toString();

    painter->drawText(col1, Qt::AlignLeft, quantita);
    painter->drawText(col2, Qt::AlignLeft, descrizione);
    painter->drawText(col3, Qt::AlignRight, imponibile);
    painter->drawText(col4, Qt::AlignRight, subtotale);

    painter->drawLine(0, col1.y()+colHeight, pageWidth, col1.y()+colHeight);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, col1.y(), colWidth*i, col1.y()+colHeight);
    }
}

void InventarioPrintLayout::printData()
{
    const int ROW_X_PAGE = (pageHeight-titleHeight)/colHeight;
    int row = 0;
    for (int i=0, page=1; i<articoloModel->rowCount(); i++, row++) {
        if (i%ROW_X_PAGE == 0 && i!=0) {
            printer->newPage();
            row = 0;
            printHeader(titleStr.arg(++page));
        }
        printRow(row+1, articoloModel->record(i));
    }
    printTotale(row+1);
}

void InventarioPrintLayout::initPainter()
{
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void InventarioPrintLayout::setRow(int row)
{
    col1.moveTop(row*colHeight+titleHeight);
    col2.moveTop(row*colHeight+titleHeight);
    col3.moveTop(row*colHeight+titleHeight);
    col4.moveTop(row*colHeight+titleHeight);
}

void InventarioPrintLayout::printTotale(int row)
{
    setRow(row);
    const QString INVENTARIO_TOT = QString::fromUtf8("SELECT sum(\"Imponibile\"*\"Quantità\") AS \"Totale\" FROM vw_magazzino WHERE \"Quantità\"!=0");

    QSqlQuery query(INVENTARIO_TOT);
    query.first();
    QString totale = query.record().value("Totale").toString();
    QString msg = "Totale: %1";

    QRect coltot(colWidth*4+margin, col1.y(), (colWidth*2)-margin*2, colHeight);

    painter->drawText(coltot, Qt::AlignRight, msg.arg(totale));
    painter->drawLine(col3.x()-margin, col1.y()+colHeight, pageWidth, col1.y()+colHeight);
    painter->drawLine(colWidth*4, col1.y(), colWidth*4, col1.y()+colHeight);
    painter->drawLine(colWidth*6, col1.y(), colWidth*6, col1.y()+colHeight);
}
