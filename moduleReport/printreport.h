#ifndef PRINTREPORT_H
#define PRINTREPORT_H

#include "moduleMagazzino/magazzino_const.h"
#include "report_const.h"

#include <QDialog>
#include <QDate>
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QSqlRecord>
#include "custommodel.h"

namespace Ui {
class PrintReport;
}

class PrintReport : public QDialog
{
    Q_OBJECT

public:
    explicit PrintReport(QString forn, report::Documenti reportType, QWidget *parent = 0);
    explicit PrintReport(CustomModel *model, QString forn, report::Documenti reportType, QWidget *parent = 0);

    ~PrintReport();

private:
    Ui::PrintReport *ui;
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
    report::Documenti report;

    QRect col1;
    QRect col2;
    QRect col3;
    QRect col4;
    QRect title;

    QPrinter *printer;
    QPainter *painter;

    void setReport(report::Documenti reportType);
    void printHeader(QString titleStr);
    void printRow(int row, QSqlRecord record);
    void printData(report::Documenti reportType);
    void initPainter();
    void setRow(int row);
    void printTotale(int row);

signals:

public slots:
    void print();

};

#endif // PRINTREPORT_H
