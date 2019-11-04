#ifndef AGENTIADDDIALOG_H
#define AGENTIADDDIALOG_H

#include <QDialog>
#include <QMap>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "libs/error.h"
#include "libs/gestionale_const.h"
#include "libs/custominsertdialog.h"
#include "agenti_const.h"

namespace Ui {
class AgentiAddDialog;
}

class AgentiAddDialog : public CustomInsertDialog
{
    Q_OBJECT
    
public:
    explicit AgentiAddDialog(QWidget *parent = 0);
    ~AgentiAddDialog();
    void setValue(QString id="");

private:
    Ui::AgentiAddDialog *ui;
    QMap <QString, QString> mapAgente;
    void initForm();
    void initComboBox();

public slots:
    void save(void);
};

#endif // AGENTIADDDIALOG_H
