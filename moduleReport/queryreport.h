#ifndef QUERYREPORT_H
#define QUERYREPORT_H

#include <QObject>
#include <QSqlQuery>
#include <QPainter>
#include <QPrinter>
#include <QPointF>
#include <QSqlError>
#include "row.h"

class QueryReport : public QObject
{
    Q_OBJECT
public:
    explicit QueryReport(QPrinter *printer, QPainter *painter, QObject *parent = 0);
    ~QueryReport();

    void setTitle(QString title) {m_titleStr = title;}
    QString getTitle() const {return m_titleStr;}

    void setTitleBgColor(QColor color=Qt::transparent) {m_titleBgColor = color;}
    QColor getTitleBgColor() const {return m_titleBgColor;}

    void setTitleFgColor(QColor color=Qt::transparent) {m_titleFgColor = color;}
    QColor getTitleFgColor() const {return m_titleFgColor;}

    void setTitleFont(QFont font){m_titleFont = font;}
    QFont getTitleFont() const {return m_titleFont;}

    void setOrigin(QPointF origin) {m_origin = origin;}
    QPointF getOrigin() const {return m_origin;}

    void setWidth(float width) {m_width = width;}
    float getwitdh() const {return m_width;}

    float getBottom() const {return m_bottom;}

    void setQuery(QString query){m_query = query;}
    QString getQuery() const {return m_query;}
    int getQuerySize() const {return m_querySize;}

    void setQueryCols(QStringList list) {m_queryCols = list;}
    QStringList getQueryCols() const {return m_queryCols;}

    void setStretchValues(QVector<int>list){m_stretchValues = list;}
    QVector<int> getStretchValues() const {return m_stretchValues;}

    void setHeaderNames(QStringList list){m_headerNames = list;}
    QStringList getHeaderNames(){return m_headerNames;}

    void setHeaderBgColor(QColor color=Qt::transparent) {m_headerBgColor = color;}
    QColor getHeaderBgColor() const {return m_headerBgColor;}

    void setHeaderFgColor(QColor color=Qt::transparent) {m_headerFgColor = color;}
    QColor getHeaderFgColor() const {return m_headerFgColor;}

    void setHeaderFont(QFont font){m_headerFont = font;}
    QFont getHeaderFont() const {return m_headerFont;}

    void setRowBgColor(QColor color=Qt::transparent) {m_rowBgColor = color;}
    QColor getRowBgColor() const {return m_rowBgColor;}

    void setRowFgColor(QColor color=Qt::transparent) {m_rowFgColor = color;}
    QColor getRowFgColor() const {return m_rowFgColor;}

    void setRowFont(QFont font){m_rowFont = font;}
    QFont getRowFont() const {return m_rowFont;}

    void setAlignCols(QVector<Qt::Alignment> list) {m_alignCols = list;}
    QVector<Qt::Alignment> getAlignCols() {return m_alignCols;}

    void draw();

private:
    QPrinter *m_printer;
    QPainter *m_painter;

    QString m_query;
    int m_querySize;
    int m_current_page;
    QString m_titleStr;

    QColor m_titleBgColor;
    QColor m_titleFgColor;
    QFont m_titleFont;

    QColor m_headerBgColor;
    QColor m_headerFgColor;
    QFont m_headerFont;

    QColor m_rowBgColor;
    QColor m_rowFgColor;
    QFont m_rowFont;

    QVector<int>m_stretchValues;
    QStringList m_headerNames;
    QStringList m_queryCols;
    QVector<Qt::Alignment>m_alignCols;

    QPointF m_origin;
    float m_width;
    float m_bottom;
    bool m_isNewPage;
    Row *m_titleRow;
    Row *m_headerRow;
    Row *m_dataRow;

    void nextPage();
    void configPage();

signals:

public slots:
};

#endif // QUERYREPORT_H
