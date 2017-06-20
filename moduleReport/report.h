#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
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
    explicit Report(QVector<int> columnsStretch={1,3,1,1}, QObject *parent = 0);
    ~Report();

    void setPen(QColor color=QColor(Qt::black), int width=10);
    bool startPrinting(bool dlg=false);
    void endPrinting();
    void print(QStringList list, QVector<Qt::Alignment> align={}, bool bold=false, bool border=true);
    void setTitle(QString title){titleText = title;}
    void setHeaderNames(QStringList list){headerNames=list;}

private:
    QPrinter *printer;
    QPainter *painter;
    QVector<int> colsStretch;
    QPen pen;
    QVector <QRectF> cols;
    QRectF title1Rect;
    QRectF title2Rect;
    QStringList headerNames;

    int colsNumber;   //numero di colonne del foglio
    float textMargin; //margine da applicare al testo nelle celle
    float rowHeight;  //altezza della riga
    int maxRowNumber; //numero di righe per foglio
    int currentPage;
    int currentRow;
    QString titleText;

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
