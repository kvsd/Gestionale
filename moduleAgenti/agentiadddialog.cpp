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
    query.prepare(SELECT_QUERY);
    query.bindValue(":id", id);
    query.exec();
    query.first();
    ui->nomeLineEdit->setText(query.value(agenti::COL_NOME).toString());
    ui->cognomeLineEdit->setText(query.value(agenti::COL_COGNOME).toString());
    ui->telLineEdit->setText(query.value(agenti::COL_TEL).toString());
    ui->celLineEdit->setText(query.value(agenti::COL_CEL).toString());
    ui->emailLineEdit->setText(query.value(agenti::COL_EMAIL).toString());
    mapAgente[keymap::KEY_ID] = id;
}

void AgentiAddDialog::save(void)
{
    qDebug() << "AgentiAddDialog::save()";
    mapAgente[keymap::KEY_NOME] = ui->nomeLineEdit->text();
    mapAgente[keymap::KEY_COGNOME] = ui->cognomeLineEdit->text();
    mapAgente[keymap::KEY_TEL] = ui->telLineEdit->text();
    mapAgente[keymap::KEY_CEL] = ui->celLineEdit->text();
    mapAgente[keymap::KEY_EMAIL] = ui->emailLineEdit->text();

    if (mapAgente[keymap::KEY_COGNOME].isEmpty()) {
        showDialogError(this, ERR008, MSG021); //NOTE codice errore 008
        ui->cognomeLineEdit->setStyleSheet(CSS_WARNING_STYLE);
        return;
    }

    QSqlQuery query;
    if (mapAgente.contains(keymap::KEY_ID)) {
        query.prepare(UPDATE_QUERY);
        query.bindValue(":id", mapAgente[keymap::KEY_ID]);
    }
    else {
        query.prepare(ADD_QUERY);
    }

    query.bindValue(":nome", mapAgente[keymap::KEY_NOME]);
    query.bindValue(":cognome", mapAgente[keymap::KEY_COGNOME]);
    query.bindValue(":tel", mapAgente[keymap::KEY_TEL]);
    query.bindValue(":cel", mapAgente[keymap::KEY_CEL]);
    query.bindValue(":email", mapAgente[keymap::KEY_EMAIL]);

    if (!query.exec()) {
        showDialogError(this, ERR009, MSG022, query.lastError().text()); //NOTE codice errore 009
        return;
    }

    this->accept();
}
