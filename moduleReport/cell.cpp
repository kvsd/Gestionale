#include "cell.h"

Cell::Cell(QPointF origin, float width, int textRows,
           QPainter *painter, QObject *parent)
    : QObject(parent),
      m_origin(origin),
      m_width(width),
      m_textRows(textRows),
      m_painter(painter),
      m_brush(QBrush(Qt::transparent)),
      m_pen_line(QPen(Qt::black, 2)),
      m_pen_header(QPen(Qt::black)),
      m_pen_text(QPen(Qt::black)),
      m_align(Qt::AlignLeft)
{
    qDebug() << "Cell()";
    makeRect();
}

Cell::~Cell()
{
    qDebug() << "~Cell()";
}

void Cell::moveCell(QPointF point)
{
    qDebug() << "Cell::moveCell(QPointF point)";
    m_origin = point;
    m_rect.moveTo(point);
}

void Cell::moveCell(float x, float y)
{
    qDebug() << "Cell::moveCell(float x, float y)";
    m_origin = QPointF(x, y);
    m_rect.moveTo(x, y);
}

void Cell::setHeaderFont(QFont font, bool bold)
{
    qDebug() << "Cell::setHeaderFont(font, bold)";
    font.setBold(bold);
    m_headerFont = font;
    makeRect();
}

void Cell::setRowHeight(int rowNumber)
{
    qDebug() << "Cell::setRowHeight(rowNumber)";
    m_textRows = rowNumber;
    makeRect();
}

void Cell::setTextFont(QFont font, bool bold)
{
    qDebug() << "Cell::setTextFont(font, bold)";
    font.setBold(bold);
    m_textFont = font;
    makeRect();
}

void Cell::setWidth(float width)
{
    qDebug() << "Cell::setWidth(width)";
    m_width = width;
    m_rect.setWidth(m_width);
}

void Cell::makeRect()
{
    qDebug() << "Cell:makeRect()";
    m_painter->save();

    //Calcolo l'altezza del testo
    m_painter->setFont(m_textFont);
    int h2 = m_painter->fontMetrics().height();

    //Calcolo l'altezza dell'intestazione
    int h1 = h2;
    if (!m_header.isEmpty() && m_textRows>1) {
        m_painter->setFont(m_headerFont);
        h1 = m_painter->fontMetrics().height();
    }

    m_margin = h2/3.0;
    m_height = h1 + h2*(m_textRows-1) + m_margin*2;

    m_rect = QRectF(m_origin, QSizeF(m_width, m_height));
    m_painter->restore();
}

void Cell::draw()
{
    qDebug() << "Cell::draw()";
    //Stampa la cella
    m_painter->save();
    m_painter->setBrush(m_brush);
    m_painter->setPen(m_pen_line);
    m_painter->drawRect(m_rect);

    //Aggiungo il margine per la stampa del testo
    QRectF rect = m_rect;
    rect.adjust(m_margin, m_margin, -m_margin, -m_margin);

    //LineSpacing -> altezza font + interlinea
    int row = m_textRows;

    //Stampa l'intestazione della cella se presente,
    //e se e' piu' grande di una riga.
    if (!m_header.isEmpty() && m_textRows>1) {
        m_painter->setFont(m_headerFont);
        int lineHeight = m_painter->fontMetrics().lineSpacing();
        m_painter->setPen(m_pen_header);
        m_painter->drawText(rect, m_header.split("\n").first());
        rect.adjust(0, lineHeight, 0, 0);
        row--;
    }

    //Stampo il testo
    if (!m_text.isEmpty()) {
        m_painter->setFont(m_textFont);
        int lineHeight = m_painter->fontMetrics().lineSpacing();
        m_painter->setPen(m_pen_text);
        for (QString str : m_text.split("\n")) {
            if (row-- == 0) break; //per linee di testo in eccesso
            m_painter->drawText(rect, str, m_align);
            rect.adjust(0, lineHeight, 0, 0);
        }
    }
    m_painter->restore();
}
