#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUsername() const
{
    return username;
}

QString LoginDialog::getPassword() const
{
    return password;
}

void LoginDialog::connectToDatabase(void)
{
    username = ui->le_username->text();
    password = ui->le_password->text();
}

void LoginDialog::openConfigDialog(void)
{
    ConnectionSetupDialog dlg(this);
    dlg.exec();
}
