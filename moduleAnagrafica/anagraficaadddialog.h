#ifndef ANAGRAFICAADDDIALOG_H
#define ANAGRAFICAADDDIALOG_H

#include "error.h"
#include "utils/controllodati.h"
#include "utils/simpledialogs.h"
#include "utils/enum_const.h"
#include "moduleAgenti/agentiadddialog.h"

#include <QDialog>
#include <QMap>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


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
    QMap <QString, QString> persona;
    QSqlTableModel *model_tipo_ditta;
    QSqlTableModel *model_citta;
    QSqlTableModel *model_provincia;
    QSqlTableModel *model_cap;
    QSqlTableModel *model_stato;
    QSqlTableModel *model_agente;

    void prepareMap(void);
    QSqlQuery prepareQuery(void);

public slots:
    void save(void);
    void open_add_tipoditta(void);
    void open_add_citta(void);
    void open_add_provincia(void);
    void open_add_cap(void);
    void open_add_stato(void);
    void open_add_agente(void);
    void copy_prt_iva(void);
};

#endif // ANAGRAFICAADDDIALOG_H
