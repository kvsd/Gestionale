#ifndef CONFIGPRINTDIALOG_H
#define CONFIGPRINTDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>

#include "moduleMagazzino/magazzino_const.h"
#include "report_const.h"

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
    void initComboBoxs();
    void loadSettings();

public slots:
    void save();

};

#endif // CONFIGPRINTDIALOG_H
