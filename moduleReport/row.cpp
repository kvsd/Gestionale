#include "row.h"

Row::Row(QVector<int> colsStretch, QPointF origin, float width,
         int textLines, QPainter *painter, QObject *parent)
    :QObject(parent),
      m_painter(painter),
      m_origin(origin),
      m_width(width),
      m_textLines(textLines)
{
    qDebug() << "Row::Row()";
    makeCols(colsStretch);
}

Row::~Row()
{
    qDebug() << "Row::~Row()";
}

Cell * Row::at(int index)
{
    qDebug() << "Row::at(index)";
    if (index < m_vector.count())
        return m_vector.at(index);
    else
        return nullptr;
}

void Row::moveRow(QPointF origin)
{
    qDebug() << "Row::moveRow(origin)";
    m_origin = origin;
    for (Cell *c : m_vector) {
        c->moveCell(c->getLeft(), origin.y());
    }
}

void Row::setHeader(QStringList textList)
{
    qDebug() << "Row::setHeader(textList)";
    for (int i=0; i<m_vector.count(); i++) {
        QString text = textList.value(i, "");
        m_vector.at(i)->setHeader(text);
    }
}

void Row::setText(QStringList textList)
{
    qDebug() << "Row::setText(textList)";
    for (int i=0; i<m_vector.count(); i++) {
        QString text = textList.value(i, "");
        m_vector.at(i)->setText(text);
    }
}

void Row::draw()
{
    qDebug() << "Row::draw()";
    for (Cell *c : m_vector) {
        c->draw();
    }
}

void Row::makeCols(QVector<int> colsStretch)
{
    qDebug() << "Row::makeCols()";
    m_vector.clear();
    if (colsStretch.isEmpty())
        colsStretch = {1};

    //Pulisco il vettore colsStretch e ottengo la quantita di colonne
    int cols = 0;
    for (int &i : colsStretch) {
        i = (i>0) ? i : 1;
        cols += i;
    }

    m_colWidth = m_width/cols;

    //Creo le celle e le aggiungo al vettore m_vector
    float x = m_origin.x();
    float y = m_origin.y();
    for (int i=0; i<colsStretch.count(); i++) {
        QPointF origin(x, y);
        float cellWidth = m_colWidth*colsStretch[i];
        Cell *c = new Cell(origin, cellWidth, m_textLines, m_painter, this);
        x += cellWidth;
        m_vector.append(c);
    }
}
