#ifndef AZIENDADIALOG_H
#define AZIENDADIALOG_H

#include "libs/error.h"
#include "libs/simpledialogs.h"
#include "libs/controllodati.h"
#include "libs/gestionale_const.h"

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>

namespace Ui {
class AziendaDialog;
}

class AziendaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AziendaDialog(QWidget *parent = 0);
    ~AziendaDialog();

private:
    Ui::AziendaDialog *ui;
    QSqlTableModel *modelCitta;
    QSqlTableModel *modelProvincia;
    QSqlTableModel *modelCap;
    QSqlTableModel *modelStato;
    QMap <QString, QString> azienda;

    void setValue(QString id="0");
    void prepareMap(void);

public slots:
    void open_add_citta(void);
    void open_add_provincia(void);
    void open_add_cap(void);
    void open_add_stato(void);
    void save(void);
    void clearCombobox(void);
    void copy_prt_iva(void);
};

#endif // AZIENDADIALOG_H
