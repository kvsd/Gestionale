#ifndef AZIENDADIALOG_H
#define AZIENDADIALOG_H

#include "../error.h"
#include "utils/simpledialogs.h"
#include "utils/controllodati.h"
#include "utils/enum_const.h"

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
    QSqlTableModel *model_citta;
    QSqlTableModel *model_provincia;
    QSqlTableModel *model_cap;
    QSqlTableModel *model_stato;
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
