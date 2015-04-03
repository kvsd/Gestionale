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
    modelUserAuth = new QSqlQueryModel(this);

    updateModel();

    ui->UserListView->setModel(modelUserList);
    ui->AuthListView->setModel(modelUserAuth);
}

void UserDbDialog::updateModel()
{
    qDebug() << "UserDbDialog::updateModel()";
    modelUserList->setQuery("SELECT usename FROM pg_user WHERE usename!='postgres'");
    modelUserAuth->setQuery("SELECT name FROM user_db");
}

void UserDbDialog::userAdd()
{
    qDebug() << "UserDbDialog::userAdd()";
    QString username = QInputDialog::getText(this, "Username", "Immettere nome utente:");
    QString password = QInputDialog::getText(this, "Password", "Immettere la password:", QLineEdit::Password);

    if (username.isEmpty() || password.isEmpty()) {
        showDialogError(this, "ERRORE", "ERRORE");
        return;
    }

    updateModel();
}

void UserDbDialog::userMod()
{
    qDebug() << "UserDbDialog::userMod()";
    return;
}

void UserDbDialog::userDel()
{
    qDebug() << "UserDbDialog::userDel()";
    return;
}

void UserDbDialog::userAddAuth()
{
    qDebug() << "UserDbDialog::userAddAuth()";
    return;
}

void UserDbDialog::userRemoveAuth()
{
    qDebug() << "UserDbDialog::userRemoveAuth()";
    return;
}
