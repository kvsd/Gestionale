#ifndef ARTICOLODIALOG_H
#define ARTICOLODIALOG_H

#include "libs/simpledialogs.h"
#include "libs/gestionale_const.h"
#include "libs/utils.h"
#include "magazzino_const.h"
#include "moduleAnagrafica/anagraficaadddialog.h"

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
    void setValue(QString id, bool update=true);

private:
    Ui::ArticoloDialog *ui;
    QSqlTableModel *modelCatMerce;
    QSqlTableModel *modelCodIva;
    QSqlQueryModel *modelFornitore;
    QSqlTableModel *modelMarca;
    QSqlTableModel *modelSede;
    QSqlTableModel *modelUnita;
    QMap <QString,QString> articoloMap;
    QSettings settings;

    void initModel(void);
    void initComboBox(void);
    void prepareMap(void);
    QSqlQuery prepareQueryArticolo(void);
    QSqlQuery prepareQueryStorico(void);
    void freezeLineEdit(QLineEdit *le, bool);

public slots:
    void updatePrezzoFattura(void);
    void calculatePrezzoAcquisto(void);
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
    void copyCodArt(void);

};

#endif // ARTICOLODIALOG_H
