#ifndef OPTIONSANAGRAFICADIALOG_H
#define OPTIONSANAGRAFICADIALOG_H

#include <QMap>
#include <QDebug>

#include "libs/custommodel.h"
#include "libs/optionsdialog.h"
#include "anagrafica_const.h"

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
    Ui::OptionsAnagraficaDialog *ui;
    CustomModel *m_anagraficaModel;
    QMap <int, QString> m_anagraficaNameCols;

    void populateAnagraficaList(void);

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
};

#endif // OPTIONSANAGRAFICADIALOG_H
