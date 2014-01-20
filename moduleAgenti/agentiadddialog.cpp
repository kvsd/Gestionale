#include "agentiadddialog.h"
#include "ui_agentiadddialog.h"

const QString ADD_QUERY = "INSERT INTO agenti(nome, cognome, tel, cel, email) VALUES(:nome, :cognome, :tel, :cel, :email)";
const QString UPDATE_QUERY = "UPDATE agenti SET nome=:nome, cognome=:cognome, tel=:tel, cel=:cel, email=:email WHERE id=:id";
const QString SELECT_QUERY = "SELECT * FROM agenti WHERE id=:id";

const QString CSS_WARNING_STYLE = "background-color: yellow";

AgentiAddDialog::AgentiAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgentiAddDialog)
{
    ui->setupUi(this);
}

AgentiAddDialog::~AgentiAddDialog()
{
    delete ui;
}

void AgentiAddDialog::setValue(QString id)
{
    QSqlQuery query;
    query.prepare(SELECT_QUERY);
    query.bindValue(":id", id);
    query.exec();
    query.first();
    ui->nomeLineEdit->setText(query.value(agenti::COL_NOME).toString());
    ui->cognomeLineEdit->setText(query.value(agenti::COL_COGNOME).toString());
    ui->telLineEdit->setText(query.value(agenti::COL_TEL).toString());
    ui->celLineEdit->setText(query.value(agenti::COL_CEL).toString());
    ui->emailLineEdit->setText(query.value(agenti::COL_EMAIL).toString());
    mapAgente["id"] = id;
}

void AgentiAddDialog::save(void)
{
    mapAgente["nome"] = ui->nomeLineEdit->text();
    mapAgente["cognome"] = ui->cognomeLineEdit->text();
    mapAgente["tel"] = ui->telLineEdit->text();
    mapAgente["cel"] = ui->celLineEdit->text();
    mapAgente["email"] = ui->emailLineEdit->text();

    if (mapAgente["cognome"].isEmpty()) {
        showDialogError(this, ERR008, MSG021); //NOTE codice errore 008
        ui->cognomeLineEdit->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }

    QSqlQuery query;
    if (mapAgente.contains("id")) {
        query.prepare(UPDATE_QUERY);
        query.bindValue(":id", mapAgente["id"]);
    }
    else {
        query.prepare(ADD_QUERY);
    }

    query.bindValue(":nome", mapAgente["nome"]);
    query.bindValue(":cognome", mapAgente["cognome"]);
    query.bindValue(":tel", mapAgente["tel"]);
    query.bindValue(":cel", mapAgente["cel"]);
    query.bindValue(":email", mapAgente["email"]);

    if (!query.exec()) {
        showDialogError(this, ERR009, MSG022, query.lastError().text()); //NOTE codice errore 009
        return;
    }

    this->accept();
}
