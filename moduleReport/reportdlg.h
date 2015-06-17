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
#include <QStandardItemModel>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QSqlRecord>
#include <QMessageBox>

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
    QSqlQueryModel *m_printModel;
    QStandardItemModel *m_ordineModel;
    QSqlQueryModel *m_fornitoreModel;
    QSettings m_settings;
    int m_pageWidth;
    int m_pageHeight;
    float m_colWidth;

    QString m_fornitore;
    QString m_titleStr;
    QString m_col1Name;
    QString m_col2Name;
    QString m_col3Name;
    QString m_col4Name;

    QRect m_col1Rect;
    QRect m_col2Rect;
    QRect m_col3Rect;
    QRect m_col4Rect;
    QRect m_titleRect;

    QString CURRENT_DATE;
    QString CURRENT_YEARS;

    QPrinter *m_printer;
    QPainter *m_painter;

    void initComboBox();
    bool setupPrinter();
    bool initPainter();
    void setReport();
    void initOrderView(QSqlQueryModel *model);
    void printHeader(QString m_titleStr);
    void printRow(int row, QStringList rowValues);
    QStringList getFields(QSqlRecord record);
    QStringList getFields(QList<QStandardItem *> items);
    void printData();
    void setRow(int row);
    void printTotale(int row);

signals:

public slots:
    void print();
    void launchConfigDlg();
    void showOptions(QString text);
    void updateFornitore(QString fornitore);


};

#endif // REPORTDLG_H
