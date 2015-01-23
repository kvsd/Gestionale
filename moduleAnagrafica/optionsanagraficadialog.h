#ifndef OPTIONSANAGRAFICADIALOG_H
#define OPTIONSANAGRAFICADIALOG_H

#include "libs/utils.h"
#include "libs/custommodel.h"
#include "anagrafica_const.h"
#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QSettings>
#include <QColorDialog>
#include <QModelIndex>

namespace Ui {
class OptionsAnagraficaDialog;
}

class OptionsAnagraficaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsAnagraficaDialog(CustomModel *model, QWidget *parent = 0);
    ~OptionsAnagraficaDialog();

private:
    Ui::OptionsAnagraficaDialog *ui;
    QMap <int, QString> anagraficaNameCols;
    QSettings settings;
    CustomModel *anagraficaModel;

    void prepareMap(void);
    void populateAnagraficaList(void);

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
    void setColumnColor(QModelIndex);
};

#endif // OPTIONSANAGRAFICADIALOG_H
