#include "agentiadddialog.h"
#include "ui_agentiadddialog.h"

AgentiAddDialog::AgentiAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentiAddDialog),
    id("-1")
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
    query.prepare(agenti::SELECT_FROM_ID);
    query.bindValue(ph::ID, id);
    query.exec();
    query.first();
    ui->nomeLineEdit->setText(query.value(coldb::NOME).toString());
    ui->cognomeLineEdit->setText(query.value(coldb::COGNOME).toString());
    ui->telLineEdit->setText(query.value(coldb::TEL).toString());
    ui->faxLineEdit->setText(query.value(coldb::FAX).toString());
    ui->celLineEdit->setText(query.value(coldb::CEL).toString());
    ui->emailLineEdit->setText(query.value(coldb::EMAIL).toString());
    mapAgente[ph::ID] = id;
}

QString AgentiAddDialog::getId()
{
    qDebug() << "AgentiAddDialog::getValue()";
    return id;
}

void AgentiAddDialog::save(void)
{
    qDebug() << "AgentiAddDialog::save()";
    mapAgente[ph::NOME] = ui->nomeLineEdit->text();
    mapAgente[ph::COGNOME] = ui->cognomeLineEdit->text();
    mapAgente[ph::TEL] = ui->telLineEdit->text();
    mapAgente[ph::FAX] = ui->faxLineEdit->text();
    mapAgente[ph::CEL] = ui->celLineEdit->text();
    mapAgente[ph::EMAIL] = ui->emailLineEdit->text();

    if (mapAgente[ph::COGNOME].isEmpty()) {
        showDialogError(this, ERR008, MSG021); //NOTE codice errore 008
        ui->cognomeLineEdit->setStyleSheet(agenti::CSS_WARNING_STYLE);
        return;
    }

    QSqlQuery query;
    if (mapAgente.contains(ph::ID)) {
        query.prepare(agenti::UPDATE_QUERY);
        query.bindValue(ph::ID, mapAgente[ph::ID]);
    }
    else {
        query.prepare(agenti::INSERT_QUERY);
    }

    query.bindValue(ph::NOME, mapAgente[ph::NOME]);
    query.bindValue(ph::COGNOME, mapAgente[ph::COGNOME]);
    query.bindValue(ph::TEL, mapAgente[ph::TEL]);
    query.bindValue(ph::FAX, mapAgente[ph::FAX]);
    query.bindValue(ph::CEL, mapAgente[ph::CEL]);
    query.bindValue(ph::EMAIL, mapAgente[ph::EMAIL]);

    if (!query.exec()) {
        showDialogError(this, ERR009, MSG022, query.lastError().text()); //NOTE codice errore 009
        return;
    }

    while (query.next())
        id = query.value("id").toString();

    this->accept();
}
