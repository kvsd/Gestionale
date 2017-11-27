#ifndef AGENTIADDDIALOG_H
#define AGENTIADDDIALOG_H

#include "libs/error.h"
#include "libs/gestionale_const.h"
#include "agenti_const.h"

#include <QDialog>
#include <QMap>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class AgentiAddDialog;
}

class AgentiAddDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AgentiAddDialog(QWidget *parent = 0);
    ~AgentiAddDialog();
    void setValue(QString id="");
    QString getId();

private:
    Ui::AgentiAddDialog *ui;
    QMap <QString, QString> mapAgente;
    QString id;

public slots:
    void save(void);


};

#endif // AGENTIADDDIALOG_H
