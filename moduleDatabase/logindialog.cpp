#include "logindialog.h"
#include "ui_logindialog.h"

const QString DEFAULT_USER = "user";
const QString DEFAULT_HOST = "localhost";
const int DEFAULT_PORT = 5432;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    qDebug() << "LoginDialog()";
    ui->setupUi(this);

    db = QSqlDatabase::database();
    db.close();
}

LoginDialog::~LoginDialog()
{
    qDebug() << "~LoginDialog()";
    delete ui;
}


void LoginDialog::connectToDatabase(void)
{
    qDebug() << "LoginDialog::connectToDatabase()";

    username = ui->le_username->text();
    password = ui->le_password->text();
    QString dbname = settings.value("dbname", DEFAULT_USER).toString();
    QString hostname = settings.value("hostname", DEFAULT_HOST).toString();
    qint16 port = settings.value("port", DEFAULT_PORT).toInt();

    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);

    if (db.open()) {
        this->accept();
    }
    else {
        showDialogError(this, "ERRORE", "errore di autentificazione", db.lastError().text());
        ui->le_username->clear();
        ui->le_password->clear();
    }
}

void LoginDialog::openConfigDialog(void)
{
    qDebug() << "LoginDialog::openConfigDialog()";
    ConnectionSetupDialog dlg(this);
    dlg.exec();
}
