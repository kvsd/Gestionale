#ifndef ORDINEPRINTLAYOUT_H
#define ORDINEPRINTLAYOUT_H

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSettings>
#include <QRect>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QDebug>
#include "magazzino_const.h"

class OrdinePrintLayout
{
public:
    OrdinePrintLayout(QString fornitore, QWidget *parent);
    ~OrdinePrintLayout();
    void printHeader(QString titleStr);
    void printRow(int row, QSqlRecord record);
    void printData();

private:
    QSqlQueryModel *ordineModel;
    QSettings settings;
    int pageWidth;
    int pageHeight;
    float colWidth;
    QString titleStr;
    QString col1Name;
    QString col2Name;
    QString col3Name;
    QString col4Name;

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

#endif // ORDINEPRINTLAYOUT_H
