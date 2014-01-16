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
    ui->le_nome->setText(query.value(agenti::COL_NOME).toString());
    ui->le_cognome->setText(query.value(agenti::COL_COGNOME).toString());
    ui->le_tel->setText(query.value(agenti::COL_TEL).toString());
    ui->le_cel->setText(query.value(agenti::COL_CEL).toString());
    ui->le_email->setText(query.value(agenti::COL_EMAIL).toString());
    mapAgente["id"] = id;
}

void AgentiAddDialog::save(void)
{
    mapAgente["nome"] = ui->le_nome->text();
    mapAgente["cognome"] = ui->le_cognome->text();
    mapAgente["tel"] = ui->le_tel->text();
    mapAgente["cel"] = ui->le_cel->text();
    mapAgente["email"] = ui->le_email->text();

    if (mapAgente["cognome"].isEmpty()) {
        showDialogError(this, ERR008, MSG021); //NOTE codice errore 008
        ui->le_cognome->setStyleSheet(CSS_WARNING_STYLE);
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
