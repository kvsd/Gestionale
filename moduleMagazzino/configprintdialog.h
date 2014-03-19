#ifndef CONFIGPRINTDIALOG_H
#define CONFIGPRINTDIALOG_H

#include <QDialog>
#include "magazzino_const.h"
#include <QDebug>

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

    void populateList(void);

public slots:
    void addColumn(void);
    void removeColumn(void);
    void save(void);
};

#endif // CONFIGPRINTDIALOG_H
