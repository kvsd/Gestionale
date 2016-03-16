#ifndef AZIENDADIALOG_H
#define AZIENDADIALOG_H

#include "libs/error.h"
#include "libs/simpledialogs.h"
#include "libs/utils.h"
#include "libs/gestionale_const.h"
#include "azienda_const.h"

#include <QDialog>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QPixmap>

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
    QMap <QString, QString> mapAzienda;
    QPixmap logo;

    void initComboBox();
    void setValue(QString id="0");
    void prepareMap(void);

public slots:
    void openAddCitta(void);
    void openAddProvincia(void);
    void openAddCap(void);
    void openAddStato(void);
    void openAddLogo(void);
    void save(void);
    void clearForm(void);
    void copyPrtIva(void);
};

#endif // AZIENDADIALOG_H
