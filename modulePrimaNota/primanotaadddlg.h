#ifndef PRIMANOTAADDDLG_H
#define PRIMANOTAADDDLG_H

#include <QDialog>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

#include "primanota_const.h"
#include "libs/gestionale_const.h"
#include "libs/utils.h"

namespace Ui {
class PrimaNotaAddDlg;
}

class PrimaNotaAddDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PrimaNotaAddDlg(QWidget *parent = 0);
    ~PrimaNotaAddDlg();
    void setValue(QString id);


private:
    Ui::PrimaNotaAddDlg *ui;
    QSqlQueryModel *m_descrModel;
    QMap<QString, QString> m_mapQuery;

    void prepareMap();
    QSqlQuery prepareQuery();

public slots:
    void save();
    void updateLineEdit();
};

#endif // PRIMANOTAADDDLG_H
