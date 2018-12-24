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
#include "libs/custominsertdialog.h"

namespace Ui {
class AnagraficaAddDialog;
}

class AnagraficaAddDialog : public CustomInsertDialog
{
    Q_OBJECT
    
public:
    explicit AnagraficaAddDialog(QWidget *parent = 0);
    ~AnagraficaAddDialog();
    void setValue(QString id);

    enum class colsAgenti {ID, NOME, COGNOME};
    
private:
    Ui::AnagraficaAddDialog *ui;
    QMap <QString, QString> m_mapPersona;
    QSqlTableModel *m_modelCitta;
    QSqlTableModel *m_modelProvincia;
    QSqlTableModel *m_modelCap;
    QSqlTableModel *m_modelStato;
    QSqlTableModel *m_modelAgente;
    QSqlTableModel *m_modelTrasmissione;

    void initForm(void);     //new
    void initComboBox(void); //new
    QSqlQuery prepareQuery(void);
    bool checkValues(void);

public slots:
    void save(void);
    void openAddCitta(void);
    void openAddProvincia(void);
    void openAddCap(void);
    void openAddAgente(void);
    void copyPrtIva(void);

private slots:
    void checkAzienda();
    void checkCliente();
    void checkFornitore();
    void checkPA();
    void toggleAgente(bool status);
    void checkSDI(QString string);
};

#endif // ANAGRAFICAADDDIALOG_H
