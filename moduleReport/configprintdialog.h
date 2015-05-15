#ifndef CONFIGPRINTDIALOG_H
#define CONFIGPRINTDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>

#include "moduleMagazzino/magazzino_const.h"
#include "report_const.h"
#include "libs/utils.h"
#include <QSqlQueryModel>

namespace Ui {
class ConfigPrintDialog;
}

class ConfigPrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigPrintDialog(QWidget *parent = 0);
    ~ConfigPrintDialog();

private:
    Ui::ConfigPrintDialog *ui;
    QSettings settings;
    QSqlQueryModel *model;
    QMap <int, QString> headerMap;

    void initModel();
    void initComboBoxs();
    void loadSettings();

public slots:
    void save();

};

#endif // CONFIGPRINTDIALOG_H
