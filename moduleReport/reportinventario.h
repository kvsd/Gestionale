#ifndef REPORTINVENTARIO_H
#define REPORTINVENTARIO_H

#include "reportbase.h"
#include "report.h"
#include "error.h"
#include "report_const.h"

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class ReportInventario;
}

class ReportInventario : public ReportBase
{
    Q_OBJECT

public:
    explicit ReportInventario(QWidget *parent = 0);
    ~ReportInventario();

private:
    Ui::ReportInventario *ui;
    QString getTotale();

private slots:
    void print();
    void setReport();
};

#endif // REPORTINVENTARIO_H
