#include "report.h"

Report::Report(QPainter *painter, QPrinter *printer,
               QVector<int> columnsStretch,  QObject *parent)
    : QObject(parent),
      m_printer(printer),
      m_painter(painter),
      m_colsStretch(columnsStretch),
      m_titleText(""),
      m_colsNumber(columnsStretch.size()),
      m_textMargin(0),
      m_rowHeight(0),
      m_maxRowNumber(0),
      m_currentPage(1),
      m_currentRow(0)
{
    qDebug() << "Report";
}

Report::~Report()
{
    qDebug() << "~Report()";
}

void Report::setPen(QColor color, int width)
{
    qDebug() << "Report::setPen()";
    m_pen.setColor(color);
    m_pen.setWidth(width);
    if (m_painter->isActive())
        m_painter->setPen(m_pen);
}

void Report::setFont(QString fontFamily, int fontSize)
{
    QFont font(fontFamily, fontSize);
    m_painter->setFont(font);
}

void Report::startPrinting()
{
    qDebug() << "Report::startPrinting()";
    setPen();
    setupPage();
}

void Report::print(QStringList list, QVector<Qt::Alignment> align, bool bold, bool border)
{
    qDebug() << "Report::print()";
    if (m_currentRow == 0)
        printHeader(true);

    printRow(list, align, bold, border);
}

void Report::setupPage()
{
    qDebug() << "Report::setupPage()";
    //Inizializza diverse variabili
    int pageHeight = m_printer->height();
    int pageWidth = m_printer->width();
    int textHeight = m_painter->fontMetrics().height();
    m_textMargin = textHeight/2.0;
    m_rowHeight = textHeight+m_textMargin;
    m_maxRowNumber = pageHeight/m_rowHeight;

    //Conta il numero delle colonne e pulisce il vettore da
    //eventuali valori minori di zero
    int c = 0;
    for (int &col : m_colsStretch) {
        col =(col>0) ? col : 1;
        c+=col;
    }

    float colWidth = pageWidth/c;

    //imposta la dimensione delle colonne
    for (int i=0, tempX=0; i<m_colsNumber; i++) {
        int colFactor = m_colsStretch.value(i,1);
        m_cols.append(QRectF(tempX, 0, colWidth*colFactor, m_rowHeight));
        tempX = m_cols.last().x()+m_cols.last().width();
    }

    m_title1Rect = QRectF(0, 0, pageWidth*80/100, m_rowHeight);
    m_title2Rect = QRectF(m_title1Rect.x()+m_title1Rect.width(),
                        0, pageWidth*20/100, m_rowHeight);
}

void Report::setRow(int row)
{
    qDebug() << "Report::setRow()";
    float y = m_rowHeight*row;
    for (QRectF &col : m_cols)
        col.moveTop(y);
}

void Report::nextRow()
{
    qDebug() << "Report::nextRow()";
    setRow(++m_currentRow);
    if (m_currentRow == m_maxRowNumber)
        setNewPage();
}

void Report::printRow(QStringList list, QVector<Qt::Alignment> align, bool bold, bool border)
{
    qDebug() << "Report::printRow()";
    if (bold) {
        m_painter->save();
        auto font = m_painter->font();
        font.setBold(bold);
        m_painter->setFont(font);
    }
    for (int i=0; i<m_colsNumber; i++) {
        if (border)
            m_painter->drawRect(m_cols[i]);
        QRectF rectText (m_cols[i].adjusted(m_textMargin, 0, -m_textMargin, 0));
        m_painter->drawText(rectText,
                          align.value(i, Align::left) | Qt::TextSingleLine,
                          list.value(i));
    }
    nextRow();

    if (bold)
        m_painter->restore();
}

void Report::printTitle()
{
    qDebug() << "Report::printTitle()";
    m_painter->save();
    auto font = m_painter->font();
    font.setBold(true);
    m_painter->setFont(font);
    m_painter->drawText(m_title1Rect, m_titleText, Align::left);
    m_painter->restore();
    m_painter->drawText(m_title2Rect, QString("Pag.%1").arg(m_currentPage), Align::right);
    nextRow();
}

void Report::printHeader(bool bold)
{
    qDebug() << "Report::printHeader()";
    if (!m_titleText.isEmpty()) {
        printTitle();
    }
    QVector<Qt::Alignment> align(4, Align::center);
    printRow(m_headerNames, align, bold, true);
}

void Report::setNewPage()
{
    qDebug() << "Report::setNewPage()";
    m_printer->newPage();
    m_currentPage++;
    m_currentRow = 0;
    setRow(m_currentRow);
}
