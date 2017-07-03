#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QPainter>
#include <QPrinter>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>
/*
 * +-------------------+
 * |   Title      | Pag| Title columns
 * |--------------+----|
 * |    |    |    |    | Headers columns
 * |----+----+----+----|
 * |____|____|____|____| Data columns
 * |    |    |    |    |
 * |    |    |    |    |
 * |    |    |    |    |
 * |    |    |    |    |
 * +-------------------+
 */

namespace Align {
    const Qt::Alignment left = Qt::AlignLeft | Qt::AlignVCenter;
    const Qt::Alignment right = Qt::AlignRight | Qt::AlignVCenter;
    const Qt::Alignment center =Qt::AlignCenter | Qt::AlignVCenter;
}

class Report : public QObject
{
    Q_OBJECT

public:
    explicit Report(QPainter *painter,
                    QPrinter *printer,
                    QVector<int> columnsStretch,
                    QObject *parent = 0);
    ~Report();

    void setPen(QColor color=QColor(Qt::black), int width=10);
    void startPrinting();
    void print(QStringList list, QVector<Qt::Alignment> align={}, bool bold=false, bool border=true);
    void setTitle(QString title){m_titleText = title;}
    void setHeaderNames(QStringList list){m_headerNames=list;}

private:
    QPrinter *m_printer;
    QPainter *m_painter;
    QVector<int> m_colsStretch; //Fattore di estensione delle colonne
    QPen m_pen;
    QVector <QRectF> m_cols;    //Colonne del foglio
    QRectF m_title1Rect;
    QRectF m_title2Rect;
    QStringList m_headerNames;
    QString m_titleText;

    int m_colsNumber;   //numero di colonne del foglio
    float m_textMargin; //margine da applicare al testo nelle celle
    float m_rowHeight;  //altezza della riga
    int m_maxRowNumber; //numero di righe per foglio
    int m_currentPage;
    int m_currentRow;

    void setupPage();
    void setRow(int row);
    void nextRow();
    void printRow(QStringList list, QVector<Qt::Alignment> align={}, bool bold=false, bool border=true);
    void printTitle();
    void printHeader(bool bold=false);

signals:

public slots:
    void setNewPage();

};

#endif // REPORT_H
