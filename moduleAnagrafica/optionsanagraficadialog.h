#ifndef OPTIONSANAGRAFICADIALOG_H
#define OPTIONSANAGRAFICADIALOG_H

#include "libs/custommodel.h"
#include "libs/optionsdialog.h"
#include "anagrafica_const.h"
#include <QMap>
#include <QDebug>

namespace Ui {
class OptionsAnagraficaDialog;
}

class OptionsAnagraficaDialog : public OptionsDialog
{
    Q_OBJECT

public:
    explicit OptionsAnagraficaDialog(QWidget *parent = 0);
    ~OptionsAnagraficaDialog();

private:
    CustomModel *anagraficaModel;
    Ui::OptionsAnagraficaDialog *ui;
    QMap <int, QString> anagraficaNameCols;

    void populateAnagraficaList(void);

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
};

#endif // OPTIONSANAGRAFICADIALOG_H
