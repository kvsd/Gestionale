#ifndef REPORTDLG_H
#define REPORTDLG_H

#include "report_const.h"
#include "magazzino_const.h"
#include "configprintdialog.h"

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

namespace Ui {
class ReportDlg;
}

class ReportDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ReportDlg(QWidget *parent = 0);

    ~ReportDlg();

private:
    Ui::ReportDlg *ui;
    QSqlQueryModel *printModel;
    QSqlQueryModel *fornitoreModel;
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
    report::Documenti reportType;

    QRect col1Rect;
    QRect col2Rect;
    QRect col3Rect;
    QRect col4Rect;
    QRect titleRect;

    QString CURRENT_DATE;
    QString CURRENT_DATE_FS; //per salvataggio pdf
    QString CURRENT_YEARS;

    QPrinter *printer;
    QPainter *painter;

    void initComboBox();
    void setupPrinter();
    void initPainter();
    void setReport(report::Documenti reportType);
    void printHeader(QString titleStr);
    void printRow(int row, QSqlRecord record);
    void printData(report::Documenti reportType);
    void setRow(int row);
    void printTotale(int row);

signals:

public slots:
    void print();
    void launchConfigDlg();
    void showOptions(QString text);

};

#endif // REPORTDLG_H
