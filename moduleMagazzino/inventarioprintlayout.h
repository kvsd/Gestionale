#ifndef INVENTARIOPRINTLAYOUT_H
#define INVENTARIOPRINTLAYOUT_H

#include <QWidget>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QRect>
#include <QDebug>
#include <QPen>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>
#include "magazzino_const.h"

class InventarioPrintLayout
{
public:
    InventarioPrintLayout(QWidget *parent=0);
    ~InventarioPrintLayout();
    void printHeader(QString titleStr);
    void printRow(int row, QSqlRecord record);
    void printData();
    void printTotale(int row);

private:
    QSqlQueryModel *articoloModel;
    int pageWidth;
    int pageHeight;
    float colWidth;
    QString titleStr;

    QRect col1;
    QRect col2;
    QRect col3;
    QRect col4;
    QRect title;

    QPrinter *printer;
    QPainter *painter;

    void initPainter();
    void setRow(int row);
};

#endif // INVENTARIOPRINTLAYOUT_H
