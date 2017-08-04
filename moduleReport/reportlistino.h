#ifndef REPORTDLG_H
#define REPORTDLG_H

#include "report_const.h"
#include "magazzino_const.h"
#include "configprintdialog.h"
#include "report.h"
#include "reportbase.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QSqlRecord>
#include <QPrintDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QFont>

namespace Ui {
class ReportListino;
}

class ReportListino : public ReportBase
{
    Q_OBJECT

public:
    explicit ReportListino(QWidget *parent = 0);

    ~ReportListino();

private:
    Ui::ReportListino *ui;
    QSqlQueryModel *m_fornitoreModel;

    QString m_fornitore;

    void initComboBox();

signals:

private slots:
    void setReport();
    void print();
    void updateFornitore(QString value);
};

#endif // REPORTDLG_H
