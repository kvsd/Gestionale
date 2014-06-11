#ifndef LISTINOPRINTLAYOUT_H
#define LISTINOPRINTLAYOUT_H

#include <QWidget>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QRect>
#include <QDebug>
#include <QPen>
#include <QSqlRecord>
#include <QSettings>
#include "custommodel.h"
#include "magazzino_const.h"

class ListinoPrintLayout
{

public:
    ListinoPrintLayout(CustomModel *model, QString titleStr, QWidget *parent=0);
    ~ListinoPrintLayout();
    void printHeader(QString titleStr);
    void printRow(int row, QSqlRecord record);
    void printData();

private:
    CustomModel *articoloModel;
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

#endif // LISTINOPRINTLAYOUT_H
