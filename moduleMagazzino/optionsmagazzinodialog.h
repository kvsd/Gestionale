#ifndef OPTIONSMAGAZZINODIALOG_H
#define OPTIONSMAGAZZINODIALOG_H

#include "magazzino_const.h"
#include "libs/gestionale_const.h"

#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QSettings>
#include <QColorDialog>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QSqlQueryModel>

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
    QSqlTableModel *codIvaModel;
    QSqlQueryModel *articoloModel;
    QSqlQueryModel *storicoModel;
    QMap <int, QString> magazzinoNameCols;
    QMap <int, QString> storicoNameCols;
    QSettings settings;

    void prepareMaps(void);
    void populateList(void);

public slots:
    void saveConfig(void);
    void loadConfig(void);
    void restoreToDefault(void);
    void setColumnColorMagazzino(QModelIndex);
    void setColumnColorStorico(QModelIndex);
};

#endif // OPTIONSMAGAZZINODIALOG_H
