#include "userdbdialog.h"
#include "ui_userdbdialog.h"

UserDbDialog::UserDbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDbDialog)
{
    qDebug() << "UserDbDialog::UserDbDialog";
    ui->setupUi(this);
    initModel();
}

UserDbDialog::~UserDbDialog()
{
    qDebug() << "UserDbDialog::~UserDbDialog()";
    delete ui;
}

void UserDbDialog::initModel()
{
    qDebug() << "UserDbDialog::initModel()";
    modelUserList = new QSqlQueryModel(this);
    updateModel();
    ui->userListView->setModel(modelUserList);
}

void UserDbDialog::updateModel()
{
    qDebug() << "UserDbDialog::updateModel()";
    modelUserList->setQuery("SELECT name FROM user_db");
}

void UserDbDialog::userAdd()
{
    qDebug() << "UserDbDialog::userAdd()";

    QString username = QInputDialog::getText(this, "Nome utente", "Immettere il nome utente:");
    QString password = QInputDialog::getText(this, "Password", "Immettere la password:", QLineEdit::Password);

    updateModel();
}

void UserDbDialog::userMod()
{
    qDebug() << "UserDbDialog::userMod()";
    QString username = ui->userListView->currentIndex().data().toString();
    bool dm = showDialogWarning(this, "<b>Attenzione</b>",
                                QString("Stai per modificare la password dell'utente <b>%1</b>. "
                                        "Continuare?").arg(username));
    if (!dm) {
        return;
    }

    QString password = QInputDialog::getText(this, "Password", "Immettere la password:", QLineEdit::Password);

    QString str = QString("ALTER USER %1 WITH PASSWORD '%2'").arg(username, password);
    QSqlQuery query;
    bool ok = query.exec(str);
    if (!ok) {
        showDialogError(this, "Errore", "Errore", query.lastError().text());
    }
}

void UserDbDialog::userDel()
{
    qDebug() << "UserDbDialog::userDel()";
    QString username = ui->userListView->currentIndex().data().toString();
    bool ok = showDialogWarning(this, "<b>Attenzione</b>",
                                QString("Stai per eliminare l'utente <b>%1</b>. "
                                        "Continuare?").arg(username));
    if (!ok) {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM user_db WHERE name=:username");
    query.bindValue(":username", username);
    ok = query.exec();
    if (!ok) {
        showDialogError(this, "ERRORE", "ERRORE", query.lastError().text());
        return;
    }
    updateModel();

    if (!isUserExists(username))
        return;

    QString str = QString("DROP USER %1").arg(username);
    ok = query.exec(str);
    if (!ok) {
        showDialogError(this, "ERRORE", "ERRORE", query.lastError().text());
        return;
    }
}

bool UserDbDialog::isUserExists(QString username)
{
    qDebug() << "UserDbDialog::checkUser()";
    QSqlQuery query;
    query.prepare("SELECT true FROM pg_user WHERE usename=:username");
    query.bindValue(":username", username);
    query.exec();
    return query.first();
}

bool UserDbDialog::isUserInGroup(QString username)
{
    qDebug() << "UserDbDialog::isUserInGroup()";

    QSqlQuery query;
    query.prepare("SELECT true FROM pg_group "
                  "WHERE (SELECT usesysid FROM pg_user WHERE usename=:username) = ANY(grolist)");
    query.bindValue(":username", username);
    query.exec();
    return query.first();
}

bool UserDbDialog::isUserIsAuth(QString username)
{
    qDebug() << "UserDbDialog::isUserIsAuth()";

    QSqlQuery query;
    query.prepare("SELECT true FROM user_db WHERE name=:username");
    query.bindValue(":username", username);
    query.exec();
    return query.first();
}

bool UserDbDialog::createUser(QString username, QString password)
{
    qDebug() << "UserDbDialog::createUser()";
    QString query_str = QString("CREATE USER %1 WITH PASSWORD '%2' IN GROUP gestionale_user").arg(username, password);

    QSqlQuery query;
    bool ok = query.exec(query_str);
    if (!ok) {
        showDialogError(this, "ERRORE", "ERRORE", query.lastError().text());
        return false;
    }

    return true;
}

bool UserDbDialog::authorizedUser(QString username)
{
    qDebug() << "UserDbDialog::authorizedUser()";
    QSqlQuery query;
    query.prepare("INSERT INTO user_db(name) VALUES(:username)");
    query.bindValue(":username", username);
    bool ok = query.exec();
    if (!ok) {
        showDialogError(this, "ERRORE", "ERRORE", query.lastError().text());
        return false;
    }

    return true;
}
