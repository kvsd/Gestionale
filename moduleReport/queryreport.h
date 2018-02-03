#ifndef QUERYREPORT_H
#define QUERYREPORT_H

#include <QObject>
#include <QSqlQuery>
#include <QPainter>
#include <QPrinter>
#include <QPointF>
#include "row.h"

class QueryReport : public QObject
{
    Q_OBJECT
public:
    explicit QueryReport(QPrinter *printer, QPainter *painter, QObject *parent = 0);
    ~QueryReport();

    void setTitle(QString title) {m_titleStr = title;}
    QString getTitle() const {return m_titleStr;}

    void setOrigin(QPointF origin) {m_origin = origin;}
    QPointF getOrigin() const {return m_origin;}

    void setWidth(float width) {m_width = width;}
    float getwitdh() const {return m_width;}

    void setTitleColor(QColor color=Qt::transparent) {m_titleColor = color;}
    QColor getTitleColor() const {return m_titleColor;}

    void setTitleFont(QFont font){m_titleFont = font;}
    QFont getTitleFont() const {return m_titleFont;}

    void setQuery(QString query){m_query = query;}
    QString getQuery() const {return m_query;}

    void setQueryCols(QStringList list) {m_queryCols = list;}
    QStringList getQueryCols() const {return m_queryCols;}

    void setStretchValues(QVector<int>list){m_stretchValues = list;}
    QVector<int> getStretchValues() const {return m_stretchValues;}

    void setAlignCols(QVector<Qt::Alignment> list) {m_alignCols = list;}
    QVector<Qt::Alignment> getAlignCols() {return m_alignCols;}

    void draw();

private:
    QPrinter *m_printer;
    QPainter *m_painter;

    QString m_query;
    int m_current_page;
    QString m_titleStr;

    QColor m_titleColor;
    QFont m_titleFont;

    QVector<int>m_stretchValues;
    QStringList m_headerNames;
    QStringList m_queryCols;
    QVector<Qt::Alignment>m_alignCols;

    QPointF m_origin;
    float m_width;
    Cell *m_displayPage;
    Row *m_titleRow;
    Row *m_headerRow;
    Row *m_dataRow;

    void nextPage();
    void configPage();

signals:

public slots:
};

#endif // QUERYREPORT_H
