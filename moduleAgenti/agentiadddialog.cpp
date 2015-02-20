#include "agentiadddialog.h"
#include "ui_agentiadddialog.h"

AgentiAddDialog::AgentiAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentiAddDialog)
{
    qDebug() << "AgentiAddDialog()";
    ui->setupUi(this);
}

AgentiAddDialog::~AgentiAddDialog()
{
    qDebug() << "~AgentiAddDialog()";
    delete ui;
}

void AgentiAddDialog::setValue(QString id)
{
    qDebug() << "AgentiAddDialog::setValue()";
    QSqlQuery query;
    query.prepare(agenti::SQL_SELECT_AGENTE);
    query.bindValue(agenti::PH_ID, id);
    query.exec();
    query.first();
    ui->nomeLineEdit->setText(query.value(agenti::COL_NOME).toString());
    ui->cognomeLineEdit->setText(query.value(agenti::COL_COGNOME).toString());
    ui->telLineEdit->setText(query.value(agenti::COL_TEL).toString());
    ui->faxLineEdit->setText(query.value(agenti::COL_FAX).toString());
    ui->celLineEdit->setText(query.value(agenti::COL_CEL).toString());
    ui->emailLineEdit->setText(query.value(agenti::COL_EMAIL).toString());
    mapAgente[agenti::PH_ID] = id;
}

void AgentiAddDialog::save(void)
{
    qDebug() << "AgentiAddDialog::save()";
    mapAgente[agenti::PH_NOME] = ui->nomeLineEdit->text();
    mapAgente[agenti::PH_COGNOME] = ui->cognomeLineEdit->text();
    mapAgente[agenti::PH_TEL] = ui->telLineEdit->text();
    mapAgente[agenti::PH_FAX] = ui->faxLineEdit->text();
    mapAgente[agenti::PH_CEL] = ui->celLineEdit->text();
    mapAgente[agenti::PH_EMAIL] = ui->emailLineEdit->text();

    if (mapAgente[agenti::PH_COGNOME].isEmpty()) {
        showDialogError(this, ERR008, MSG021); //NOTE codice errore 008
        ui->cognomeLineEdit->setStyleSheet(agenti::CSS_WARNING_STYLE);
        return;
    }

    QSqlQuery query;
    if (mapAgente.contains(agenti::PH_ID)) {
        query.prepare(agenti::SQL_UPDATE_AGENTE);
        query.bindValue(agenti::PH_ID, mapAgente[agenti::PH_ID]);
    }
    else {
        query.prepare(agenti::SQL_ADD_AGENTE);
    }

    query.bindValue(agenti::PH_NOME, mapAgente[agenti::PH_NOME]);
    query.bindValue(agenti::PH_COGNOME, mapAgente[agenti::PH_COGNOME]);
    query.bindValue(agenti::PH_TEL, mapAgente[agenti::PH_TEL]);
    query.bindValue(agenti::PH_FAX, mapAgente[agenti::PH_FAX]);
    query.bindValue(agenti::PH_CEL, mapAgente[agenti::PH_CEL]);
    query.bindValue(agenti::PH_EMAIL, mapAgente[agenti::PH_EMAIL]);

    if (!query.exec()) {
        showDialogError(this, ERR009, MSG022, query.lastError().text()); //NOTE codice errore 009
        return;
    }

    this->accept();
}
