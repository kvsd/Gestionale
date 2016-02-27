#ifndef CODIVAUPDATEDIALOG_H
#define CODIVAUPDATEDIALOG_H

#include "libs/gestionale_const.h"
#include "magazzino_const.h"
#include "libs/error.h"
#include "libs/utils.h"

#include <QDate>
#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class codIvaUpdateDialog;
}

class codIvaUpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit codIvaUpdateDialog(QWidget *parent = 0);
    ~codIvaUpdateDialog();

private:
    Ui::codIvaUpdateDialog *ui;
    QSqlTableModel *oldIvaModel;
    QSqlTableModel *newIvaModel;

    void initModel(void);
    void initComboBox(void);

private slots:
    void updateIva(void);
};

#endif // CODIVAUPDATEDIALOG_H
