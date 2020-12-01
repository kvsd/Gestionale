#ifndef ARTICOLODIALOG_H
#define ARTICOLODIALOG_H

#include "libs/simpledialogs.h"
#include "libs/gestionale_const.h"
#include "libs/utils.h"
#include "libs/custominsertdialog.h"
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

class ArticoloDialog : public CustomInsertDialog
{
    Q_OBJECT

public:
    explicit ArticoloDialog(QWidget *parent = 0);
    ~ArticoloDialog();
    //void setValue(QString id, bool update=true);
    void setValue(QString id);
    void setFornitore(QString str);
    void setCategoria(QString str);
    void setMarca(QString str);
    void setSede(QString str);
    void setFattura(QString str);

private:
    Ui::ArticoloDialog *ui;
    QSqlTableModel *m_modelCatMerce;
    QSqlTableModel *m_modelCodIva;
    QSqlQueryModel *m_modelFornitore;
    QSqlTableModel *m_modelMarca;
    QSqlTableModel *m_modelSede;
    QSqlTableModel *m_modelUnita;
    QMap <QString,QString> m_articoloMap;
    QSettings m_settings;

    void initModel(void);
    void initForm(void);
    void initComboBox(void);
    void prepareMap(void);
    QSqlQuery prepareQueryArticolo(void);
    QSqlQuery prepareQueryStorico(void);
    void freezeLineEdit(QLineEdit *le, bool);
    void setMoney(QLineEdit *le);

public slots:
    void updatePrezzoFattura(void);
    void calculatePrezzoAcquisto(void);
    void updatePrezzoAcquisto(void);
    void updateIva(void);
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
