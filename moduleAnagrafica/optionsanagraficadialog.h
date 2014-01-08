#ifndef OPTIONSANAGRAFICADIALOG_H
#define OPTIONSANAGRAFICADIALOG_H

#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QSettings>

namespace Ui {
class OptionsAnagraficaDialog;
}

class OptionsAnagraficaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsAnagraficaDialog(QWidget *parent = 0);
    ~OptionsAnagraficaDialog();

private:
    Ui::OptionsAnagraficaDialog *ui;
    QMap <int, QString> anagrafica_cols;
    QSettings settings;

    void prepareMap(void);
    void populateAnagraficaList(void);

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
};

#endif // OPTIONSANAGRAFICADIALOG_H
