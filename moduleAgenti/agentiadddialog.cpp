#include "agentiadddialog.h"
#include "ui_agentiadddialog.h"

const QString ADD_QUERY = "INSERT INTO agenti(nome, cognome, tel, cel, email) VALUES(:nome, :cognome, :tel, :cel, :email)";
const QString UPDATE_QUERY = "UPDATE agenti SET nome=:nome, cognome=:cognome, tel=:tel, cel=:cel, email=:email WHERE id=:id";
const QString SELECT_QUERY = "SELECT * FROM agenti WHERE id=:id";

enum columns {COL_ID, COL_NOME, COL_COGNOME, COL_TEL, COL_CEL, COL_EMAIL};

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
    ui->le_nome->setText(query.value(COL_NOME).toString());
    ui->le_cognome->setText(query.value(COL_COGNOME).toString());
    ui->le_tel->setText(query.value(COL_TEL).toString());
    ui->le_cel->setText(query.value(COL_CEL).toString());
    ui->le_email->setText(query.value(COL_EMAIL).toString());
    agente["id"] = id;
}

void AgentiAddDialog::save(void)
{
    agente["nome"] = ui->le_nome->text();
    agente["cognome"] = ui->le_cognome->text();
    agente["tel"] = ui->le_tel->text();
    agente["cel"] = ui->le_cel->text();
    agente["email"] = ui->le_email->text();

    if (agente["cognome"].isEmpty()) {
        showDialogError(this, ERR008, MSG021); //NOTE codice errore 008
        ui->le_cognome->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }

    QSqlQuery query;
    if (agente.contains("id")) {
        query.prepare(UPDATE_QUERY);
        query.bindValue(":id", agente["id"]);
    }
    else {
        query.prepare(ADD_QUERY);
    }

    query.bindValue(":nome", agente["nome"]);
    query.bindValue(":cognome", agente["cognome"]);
    query.bindValue(":tel", agente["tel"]);
    query.bindValue(":cel", agente["cel"]);
    query.bindValue(":email", agente["email"]);

    if (!query.exec()) {
        showDialogError(this, ERR009, MSG022, query.lastError().text()); //NOTE codice errore 009
        return;
    }

    this->accept();
}
