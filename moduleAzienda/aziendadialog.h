#ifndef AZIENDADIALOG_H
#define AZIENDADIALOG_H

#include "libs/error.h"
#include "libs/simpledialogs.h"
#include "libs/utils.h"
#include "libs/gestionale_const.h"
#include "azienda_const.h"
#include "libs/custominsertdialog.h"

#include <QDialog>
#include <QFileDialog>
#include <QBuffer>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QPixmap>
#include <QComboBox>

namespace Ui {
class AziendaDialog;
}

class AziendaDialog : public CustomInsertDialog
{
    Q_OBJECT

public:
    explicit AziendaDialog(QWidget *parent = 0);
    ~AziendaDialog();
    enum cbcols {ID, DESCR, SIGLA};
    enum size {LOGO_WIDTH = 300, LOGO_HEIGHT=200};

private:
    Ui::AziendaDialog *ui;
    QSqlTableModel *m_modelCitta;
    QSqlTableModel *m_modelProvincia;
    QSqlTableModel *m_modelProvinciaREA;
    QSqlTableModel *m_modelCap;
    QSqlTableModel *m_modelStato;
    QSqlTableModel *m_modelRegFiscale;
    QSqlTableModel *m_modelLiquidazione;
    QMap <QString, QString> m_mapAzienda;
    QPixmap m_logo;

    void initComboBox();
    void setValue(QString id="0");
    void prepareMap(void);
    bool checkValues(void);

public slots:
    void clearForm(void);
    void copyPrtIva(void);
    void openAddCitta(void);
    void openAddCap(void);
    void openAddLogo(void);
    void save(void);
};

#endif // AZIENDADIALOG_H
