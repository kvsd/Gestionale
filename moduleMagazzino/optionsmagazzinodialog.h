#ifndef OPTIONSMAGAZZINODIALOG_H
#define OPTIONSMAGAZZINODIALOG_H

#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QSettings>
#include <QColorDialog>
#include <QModelIndex>

namespace Ui {
class OptionsMagazzinoDialog;
}

class OptionsMagazzinoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsMagazzinoDialog(QWidget *parent = 0);
    ~OptionsMagazzinoDialog();

private:
    Ui::OptionsMagazzinoDialog *ui;
    QMap <int, QString> magazzinoNameCols;
    QMap <int, QString> storicoNameCols;
    QSettings settings;

    void prepareMaps(void);
    void populateList(void);

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
    void setColumnColor(QModelIndex);
};

#endif // OPTIONSMAGAZZINODIALOG_H
