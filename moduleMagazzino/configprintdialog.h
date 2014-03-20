#ifndef CONFIGPRINTDIALOG_H
#define CONFIGPRINTDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>

#include "magazzino_const.h"

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
    QMap<int, QString> nameCols;
    QMap<QString, int> sizeCols;
    QSettings settings;

    void populateList(void);
    void loadSettings(void);

public slots:
    void addColumn(void);
    void removeColumn(void);
    void save(void);
};

#endif // CONFIGPRINTDIALOG_H
