#ifndef ROW_H
#define ROW_H

#include <QPainter>
#include <QObject>
#include <QVector>
#include <QDebug>
#include <QPointF>
#include "cell.h"

class Row : public QObject
{
    Q_OBJECT

public:
    explicit Row(QVector<int> colsStretch, QPointF origin, float width,
                 int textLines, QPainter *painter, QObject *parent = 0);
    Row() =delete;
    ~Row();

    Cell * at(int index);
    void moveRow(QPointF origin);
    void moveRow(float x, float y);
    void setBgColor(QColor color=Qt::transparent);
    void setFgColor(QColor color=Qt::black);
    void setLineColor(QColor color=Qt::black);
    void setTextAlignment(QVector<Qt::Alignment> aligns);
    void setHeader(QStringList textList);
    void setText(QStringList textList);
    void setTextFont(QFont font, bool bold);
    void draw();

    QPointF getOrigin() const {return m_origin;}

    float getBottom() const {return m_vector.first()->getBottom();}
    float getLeft() const {return m_origin.x();}
    float getRight() const {return m_vector.last()->getRight();}
    float getHeight() const {return m_vector.first()->getHeight();}
    float getTop() const {return m_origin.y();}
    float getWidth() const {return m_vector.last()->getRight() - m_vector.first()->getLeft();}

    int getColsNumber() const {return m_vector.count();}

private:
    QPainter *m_painter;
    QVector<Cell *> m_vector;   //QVector che contiene le celle della riga
    QPointF m_origin;           //Coordinate in alto/sinistra
    float m_width;              //Larghezza della riga
    float m_colWidth;           //Larghezza di una colonna
    float m_textLines;          //Numero di righe di testo
    QStringList m_textList;

    void makeCols(QVector<int> colsStretch);

signals:

public slots:
};

#endif // ROW_H
