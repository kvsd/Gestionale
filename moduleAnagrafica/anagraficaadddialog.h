#ifndef ANAGRAFICAADDDIALOG_H
#define ANAGRAFICAADDDIALOG_H

#include "libs/error.h"
#include "libs/utils.h"
#include "libs/simpledialogs.h"
#include "anagrafica_const.h"
#include "moduleAgenti/agentiadddialog.h"

#include <QDialog>
#include <QMap>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>


namespace Ui {
class AnagraficaAddDialog;
}

class AnagraficaAddDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AnagraficaAddDialog(QWidget *parent = 0);
    ~AnagraficaAddDialog();
    void setValue(QString id);
    
private:
    Ui::AnagraficaAddDialog *ui;
    QMap <QString, QString> mapPersona;
    QSqlTableModel *modelDitta;
    QSqlTableModel *modelCitta;
    QSqlTableModel *modelProvincia;
    QSqlTableModel *modelCap;
    QSqlTableModel *modelStato;
    QSqlTableModel *modelAgente;

    void initModel(void);
    void initComboBox(void);
    void prepareMap(void);
    QSqlQuery prepareQuery(void);

public slots:
    void save(void);
    void openAddTipoditta(void);
    void openAddCitta(void);
    void openAddProvincia(void);
    void openAddCap(void);
    void openAddStato(void);
    void openAddAgente(void);
    void copyPrtIva(void);
};

#endif // ANAGRAFICAADDDIALOG_H
