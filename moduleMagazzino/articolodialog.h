#ifndef ARTICOLODIALOG_H
#define ARTICOLODIALOG_H

#include "libs/simpledialogs.h"
#include "libs/gestionale_const.h"
#include "magazzino_const.h"

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMap>
#include <QDebug>
#include <QLocale>
#include <QSettings>

namespace Ui {
class ArticoloDialog;
}

class ArticoloDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArticoloDialog(QWidget *parent = 0);
    ~ArticoloDialog();
    void setValue(QString id);

private:
    Ui::ArticoloDialog *ui;
    QSqlTableModel *modelCatMerce;
    QSqlTableModel *modelCodIva;
    QSqlQueryModel *modelFornitore;
    QSqlTableModel *modelMarca;
    QSqlTableModel *modelSede;
    QSqlTableModel *modelUnita;
    QMap <int,QString> articolo;
    QSettings settings;

    void initModel(void);
    void initComboBox(void);
    void prepareMap(void);
    QSqlQuery prepareQueryArticolo(void);
    QSqlQuery prepareQueryStorico(void);
    double stringToDouble(QString string);

public slots:
    void updatePrezzoFattura(void);
    void updatePrezzoAcquisto(void);
    void updateIva(void);
    void updatePrezzoFinito(void);
    void updatePrezzoVendita(void);
    void save(void);
    void openAddMarca();
    void openAddCategoria();
    void openAddMisura();
    void openAddFornitore();
    void openAddIVA();
    void openAddSede();

};

#endif // ARTICOLODIALOG_H
