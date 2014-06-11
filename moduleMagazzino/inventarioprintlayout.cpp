#include "inventarioprintlayout.h"

InventarioPrintLayout::InventarioPrintLayout(QWidget *parent)
{
    qDebug() << "InventarioPrintLayout()";

    articoloModel = new QSqlQueryModel;
    articoloModel->setQuery(magazzino::SELECT_INVENTARIO);

    printer = new QPrinter(QPrinter::HighResolution);
    painter = new QPainter;

    QPrintDialog printDialog(printer, parent);
    if (printDialog.exec() == QDialog::Accepted) {
        painter->begin(printer);
        initPainter();

        titleStr = QString("Inventario %1 anno %2 pag.%3").arg("Fer.Ba.snc", QDate::currentDate().toString("yyyy"));
        pageHeight = printer->height();
        pageWidth = printer->width();
        colWidth = pageWidth/6;

        const int leftMargin = magazzino::PRINT_MARGINS;
        const int rightMargin = magazzino::PRINT_MARGINS*2;

        title = QRect(0, 0, pageWidth, magazzino::PRINT_TITLE_HEIGHT);
        col1 = QRect(colWidth*0+leftMargin, 0, (colWidth*1)-rightMargin, magazzino::PRINT_COLS_HEIGHT);
        col2 = QRect(colWidth*1+leftMargin, 0, (colWidth*3)-rightMargin, magazzino::PRINT_COLS_HEIGHT);
        col3 = QRect(colWidth*4+leftMargin, 0, (colWidth*1)-rightMargin, magazzino::PRINT_COLS_HEIGHT);
        col4 = QRect(colWidth*5+leftMargin, 0, (colWidth*1)-rightMargin, magazzino::PRINT_COLS_HEIGHT);

        printHeader(titleStr.arg(1));
        printData();
        painter->end();
    }    
}

InventarioPrintLayout::~InventarioPrintLayout()
{
    qDebug() << "~InventarioPrintLayout()";
    delete articoloModel;
    delete printer;
    delete painter;
}

void InventarioPrintLayout::printHeader(QString titleStr)
{
    qDebug() << "InventarioPrintLayout::printHeader()";
    //Stampo titolo
    painter->drawText(title, Qt::AlignLeft|Qt::AlignVCenter, titleStr, &title);

    //Stampo l'intestazione delle tabelle
    setRow(0);
    painter->drawText(col1, Qt::AlignCenter, magazzino::CMP_QT);
    painter->drawText(col2, Qt::AlignCenter, magazzino::CMP_DESCR);
    painter->drawText(col3, Qt::AlignCenter, magazzino::CMP_PRZ_ACQ);
    painter->drawText(col4, Qt::AlignCenter, magazzino::CMP_SUBTOT);

    //Stampo la cornice dell'intestazione
    painter->drawLine(0, magazzino::PRINT_TITLE_HEIGHT, pageWidth, magazzino::PRINT_TITLE_HEIGHT);
    painter->drawLine(0, magazzino::PRINT_TITLE_HEIGHT+magazzino::PRINT_COLS_HEIGHT,
                      pageWidth, magazzino::PRINT_TITLE_HEIGHT+magazzino::PRINT_COLS_HEIGHT);
    for (int i=0; i<7; i++) {
        if (i==2 || i==3) continue;
        painter->drawLine(colWidth*i, magazzino::PRINT_TITLE_HEIGHT,
                          colWidth*i, magazzino::PRINT_TITLE_HEIGHT+magazzino::PRINT_COLS_HEIGHT);
    }
}

void InventarioPrintLayout::printRow(int row, QSqlRecord record)
{
    qDebug() << "InventarioPrintLayout::printRow()";
    setRow(row);

    QString col1Value = record.value(magazzino::CMP_QT).toString();
    QString col2Value = record.value(magazzino::CMP_DESCR).toString();
    QString col3Value = record.value(magazzino::CMP_PRZ_ACQ).toString();
    QString col4Value = record.value(magazzino::CMP_SUBTOT).toString();

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

void InventarioPrintLayout::printData()
{
    qDebug() << "InventarioPrintLayout::printData()";
    const int ROW_X_PAGE = (pageHeight-magazzino::PRINT_TITLE_HEIGHT)/magazzino::PRINT_COLS_HEIGHT;
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
    qDebug() << "InventarioPrintLayout::initPainter()";
    QPen pen;
    pen.setWidth(10);
    painter->setPen(pen);
}

void InventarioPrintLayout::setRow(int row)
{
    qDebug() << "InventarioPrintLayout::setRow()";
    const int y = row*magazzino::PRINT_COLS_HEIGHT+magazzino::PRINT_TITLE_HEIGHT;
    col1.moveTop(y);
    col2.moveTop(y);
    col3.moveTop(y);
    col4.moveTop(y);
}

void InventarioPrintLayout::printTotale(int row)
{
    qDebug() << "InventarioPrintLayout::printTotale()";
    setRow(row);

    QSqlQuery query(magazzino::SQL_INVENTARIO_TOT);
    query.first();
    QString totale = query.record().value("Totale").toString();
    QString msg = "Totale: %1";

    const int leftMargin = magazzino::PRINT_MARGINS;
    const int rightMargin = magazzino::PRINT_MARGINS*2;
    QRect coltot(colWidth*4+leftMargin, col1.y(), (colWidth*2)-rightMargin, magazzino::PRINT_COLS_HEIGHT);

    painter->drawText(coltot, Qt::AlignRight, msg.arg(totale));
    painter->drawLine(col3.x()-magazzino::PRINT_MARGINS, col1.y()+magazzino::PRINT_COLS_HEIGHT,
                      pageWidth, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*4, col1.y(), colWidth*4, col1.y()+magazzino::PRINT_COLS_HEIGHT);
    painter->drawLine(colWidth*6, col1.y(), colWidth*6, col1.y()+magazzino::PRINT_COLS_HEIGHT);
}
