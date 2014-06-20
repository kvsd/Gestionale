#ifndef PRINTREPORT_H
#define PRINTREPORT_H

#include <QObject>
#include <QDate>
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QSqlRecord>
#include "magazzino_const.h"

class PrintReport : public QObject
{
    Q_OBJECT
public:
    explicit PrintReport(QString forn, magazzino::Documenti reportType, QWidget *parent = 0);
    ~PrintReport();

private:
    QSqlQueryModel *printModel;
    QSettings settings;
    int pageWidth;
    int pageHeight;
    float colWidth;

    QString fornitore;
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

    void setReport(magazzino::Documenti reportType);
    void printHeader(QString titleStr);
    void printRow(int row, QSqlRecord record);
    void printData(magazzino::Documenti reportType);
    void initPainter();
    void setRow(int row);
    void printTotale(int row);

signals:

public slots:

};

#endif // PRINTREPORT_H
