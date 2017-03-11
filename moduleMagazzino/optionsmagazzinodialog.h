#ifndef OPTIONSMAGAZZINODIALOG_H
#define OPTIONSMAGAZZINODIALOG_H

#include "magazzino_const.h"
#include "libs/gestionale_const.h"
#include "libs/optionsdialog.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
class OptionsMagazzinoDialog;
}

class OptionsMagazzinoDialog : public OptionsDialog
{
    Q_OBJECT

public:
    explicit OptionsMagazzinoDialog(QWidget *parent = 0);
    ~OptionsMagazzinoDialog();

private:
    Ui::OptionsMagazzinoDialog *ui;
    QSqlTableModel *codIvaModel;
    QSqlQueryModel *articoloModel;
    QSqlQueryModel *storicoModel;

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
};

#endif // OPTIONSMAGAZZINODIALOG_H
