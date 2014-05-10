#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    qDebug() << "LoginDialog()";
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    qDebug() << "~LoginDialog()";
    delete ui;
}

QString LoginDialog::getUsername() const
{
    qDebug() << "LoginDialog::getUsername()";
    return username;
}

QString LoginDialog::getPassword() const
{
    qDebug() << "LoginDialog::getPassword()";
    return password;
}

void LoginDialog::connectToDatabase(void)
{
    qDebug() << "LoginDialog::connectToDatabase()";
    username = ui->le_username->text();
    password = ui->le_password->text();
}

void LoginDialog::openConfigDialog(void)
{
    qDebug() << "LoginDialog::openConfigDialog()";
    ConnectionSetupDialog dlg(this);
    dlg.exec();
}
