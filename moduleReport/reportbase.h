#ifndef REPORTBASE_H
#define REPORTBASE_H

#include "report.h"
#include "libs/utils.h"

#include <QDialog>
#include <QSqlQueryModel>
#include <QPainter>
#include <QPrinter>
#include <QSettings>
#include <QSqlRecord>
#include <QDate>
#include <QPrintDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

class ReportBase : public QDialog
{
    Q_OBJECT
public:
    explicit ReportBase(QWidget *parent = 0);
    ~ReportBase();

protected:
    QSqlQueryModel *m_printModel;
    QPainter *m_painter;
    QPrinter *m_printer;
    QSettings m_settings;
    Report *m_report;

    QString m_currentDate;
    QString m_currentYears;

    QString m_titleStr;
    QStringList m_colsName;
    QVector<int> m_stretchVector;
    QStringList m_headerName;

    QStringList getFields(QSqlRecord &record);
    void setReport();
    void setupPrint();
    void endPrinting(bool status);

signals:

protected slots:

};

#endif // REPORTBASE_H
