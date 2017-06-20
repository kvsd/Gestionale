#include "report.h"

Report::Report(QVector<int> columnsStretch,  QObject *parent)
    : QObject(parent),
      printer(new QPrinter(QPrinter::HighResolution)),
      painter(new QPainter()),
      colsStretch(columnsStretch),
      colsNumber(columnsStretch.size()),
      textMargin(0),
      rowHeight(0),
      maxRowNumber(0),
      currentPage(1),
      currentRow(0),
      titleText("")
{
    qDebug() << "Report";
    //Parametri di default della stampante;
    printer->setOutputFileName("output.pdf");
    printer->setOrientation(QPrinter::Portrait);
    printer->setPageSize(QPrinter::A4);
}

Report::~Report()
{
    qDebug() << "~Report()";
    delete painter;
    delete printer;
}

void Report::setPen(QColor color, int width)
{
    qDebug() << "setPen()";
    pen.setColor(color);
    pen.setWidth(width);
    if (painter->isActive())
        painter->setPen(pen);
}

bool Report::startPrinting(bool dlg)
{
    qDebug() << "startPrinting()";
    //Configura QPainter
    if (dlg) {
        QPrintDialog dlg(printer);
        if (dlg.exec() != QPrintDialog::Accepted)
            return false;
    }

    if (!painter->begin(printer))
        return false;

    setPen();
    setupPage();
    return true;
}

void Report::endPrinting()
{
    qDebug() << "Report::endPrinting()";
    if (printer->outputFileName() != "")
        QDesktopServices::openUrl(QUrl(printer->outputFileName()));
}

void Report::print(QStringList list, QVector<Qt::Alignment> align, bool bold, bool border)
{
    if (currentRow == 0)
        printHeader(true);

    printRow(list, align, bold, border);
}

void Report::setupPage()
{
    qDebug() << "setupPage()";
    //Inizializza diverse variabili
    int pageHeight = printer->height();
    int pageWidth = printer->width();
    int textHeight = painter->fontMetrics().height();
    textMargin = textHeight/2.0;
    rowHeight = textHeight+textMargin;
    maxRowNumber = pageHeight/rowHeight;

    //Conta il numero delle colonne e pulisce il vettore da
    //eventuali valori minori di zero
    int c = 0;
    for (int &col : colsStretch) {
        col =(col>0) ? col : 1;
        c+=col;
    }

    float colWidth = pageWidth/c;

    //imposta la dimensione delle colonne
    for (int i=0, tempX=0; i<colsNumber; i++) {
        int colFactor = colsStretch.value(i,1);
        cols.append(QRectF(tempX, 0, colWidth*colFactor, rowHeight));
        tempX = cols.last().x()+cols.last().width();
    }

    title1Rect = QRectF(0, 0, pageWidth*80/100, rowHeight);
    title2Rect = QRectF(title1Rect.x()+title1Rect.width(),
                        0, pageWidth*20/100, rowHeight);
}

void Report::setRow(int row)
{
    qDebug() << "setRow()";
    float y = rowHeight*row;
    for (QRectF &col : cols)
        col.moveTop(y);
}

void Report::nextRow()
{
    qDebug() << "nextRow()";
    setRow(++currentRow);
    if (currentRow == maxRowNumber)
        setNewPage();
}

void Report::printRow(QStringList list, QVector<Qt::Alignment> align, bool bold, bool border)
{
    qDebug() << "printRow()";
    if (bold) {
        painter->save();
        auto font = painter->font();
        font.setBold(bold);
        painter->setFont(font);
    }
    for (int i=0; i<colsNumber; i++) {
        if (border)
            painter->drawRect(cols[i]);
        QRectF rectText (cols[i].adjusted(textMargin, 0, -textMargin, 0));
        painter->drawText(rectText,
                          align.value(i, Align::left) | Qt::TextSingleLine,
                          list.value(i));
    }
    nextRow();

    if (bold)
        painter->restore();
}

void Report::printTitle()
{
    qDebug() << "printTitle()";
    painter->save();
    auto font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(title1Rect, titleText, Align::left);
    painter->restore();
    painter->drawText(title2Rect, QString("Pag.%1").arg(currentPage), Align::right);
    nextRow();
}

void Report::printHeader(bool bold)
{
    qDebug() << "printHeader()";
    if (!titleText.isEmpty()) {
        printTitle();
    }
    QVector<Qt::Alignment> align(4, Align::center);
    printRow(headerNames, align, bold, true);
}

void Report::setNewPage()
{
    qDebug() << "setNewPage()";
    printer->newPage();
    currentPage++;
    currentRow = 0;
    setRow(currentRow);
}
