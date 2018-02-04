#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QPainter>
#include <QPrinter>
#include <QDebug>

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QPointF origin, float width, int textRows,
                  QPainter *painter, QObject *parent = 0);
    Cell() = delete;
    ~Cell();

    void draw();
    void moveCell(float x, float y);
    void moveCell(QPointF point);
    void setBgColor(QColor color=Qt::transparent){m_brush = QBrush(color);}
    void setFgColor(QColor color=Qt::black) {m_pen_text = color;}
    void setHeader(QString text) {m_header = text;}
    void setHeaderColor(QColor color=Qt::black) {m_pen_header = color;}
    void setHeaderFont(QFont font, bool bold=true);
    void setLineColor(QColor color=Qt::black) {m_pen_line = color;}
    void setRowHeight(int rowNumber);
    void setText(QString text) {m_text = text;}
    void setTextFont(QFont font, bool bold=false);
    void setTextAlignment(Qt::Alignment align) {m_align = align;}
    void setWidth(float width);

    inline float getBottom() const {return m_rect.bottom();}
    inline float getLeft() const {return m_rect.left();}
    inline float getRight() const {return m_rect.right();}
    inline float getTop() const {return m_rect.top();}
    inline float getHeight() const {return m_height;}
    inline float getWidth() const {return m_width;}

    inline QRectF getRect() const {return m_rect;}
    inline QPointF getOrigin() const {return m_origin;}

    inline QString getHeader() const {return m_header;}
    inline QString getText() const {return m_text;}

private:
    QPointF m_origin;
    float m_width;          //larghezza della cella
    float m_height;         //altezza della cella
    float m_margin;         //margine della cella
    int m_textRows;         //numero di righe nella cella
    QString m_header;       //Intestazione della cella
    QString m_text;         //Testo della cella
    QPainter *m_painter;
    QRectF m_rect;
    QFont m_textFont;       //Font per il testo
    QFont m_headerFont;     //Font per l'intestazione
    QBrush m_brush;         //Per impostare il colore dello sfondo
    QPen m_pen_line;        //per impostare il colore delle linee
    QPen m_pen_header;      //Per impostare il colore intestazione
    QPen m_pen_text;        //Per impostare il colore del testo
    Qt::Alignment m_align;  //Allineamento del testo

    void makeRect();

signals:

public slots:
};

#endif // CELL_H
