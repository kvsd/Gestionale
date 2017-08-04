#ifndef REPORTBASE_H
#define REPORTBASE_H

#include "configprintdialog.h"
#include <QDialog>
#include <QSqlQueryModel>
#include <QPainter>
#include <QPrinter>
#include <QSettings>
#include <QSqlRecord>
#include <QDate>
#include <QDebug>

class ReportBase : public QDialog
{
    Q_OBJECT
public:
    explicit ReportBase(QWidget *parent = 0);

protected:
    QSqlQueryModel *m_printModel;
    QPainter *m_painter;
    QPrinter *m_printer;
    QSettings m_settings;

    QString m_currentDate;
    QString m_currentYears;

    QString m_titleStr;
    QStringList m_colsName;
    QVector<int> m_stretchVector;
    QStringList m_headerName;

    QStringList getFields(QSqlRecord &record);
    virtual void setReport();

signals:

protected slots:
    void launchConfigDlg();

};

#endif // REPORTBASE_H
