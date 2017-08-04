#ifndef REPORTINVENTARIO_H
#define REPORTINVENTARIO_H

#include "reportbase.h"
#include "report.h"
#include "error.h"
#include "configprintdialog.h"

#include <QDialog>
#include <QDebug>
#include <QPrintDialog>
#include <QDesktopServices>
#include <QUrl>

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

private slots:
    void print();
    void setReport();
};

#endif // REPORTINVENTARIO_H
