#ifndef ANAGRAFICAADDDIALOG_H
#define ANAGRAFICAADDDIALOG_H

#include <QDialog>
#include <QMap>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

#include "libs/error.h"
#include "libs/utils.h"
#include "libs/simpledialogs.h"
#include "anagrafica_const.h"
#include "moduleAgenti/agentiadddialog.h"

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
    QMap <QString, QString> m_mapPersona;
    QSqlTableModel *m_modelDitta;
    QSqlTableModel *m_modelCitta;
    QSqlTableModel *m_modelProvincia;
    QSqlTableModel *m_modelCap;
    QSqlTableModel *m_modelStato;
    QSqlTableModel *m_modelAgente;

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
