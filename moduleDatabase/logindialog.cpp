#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    qDebug() << "LoginDialog()";
    ui->setupUi(this);

    if (db.contains()) {
        db = QSqlDatabase::database();
    }
    else {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
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
    QString dbname = settings.value(dbconst::dbname, dbconst::DEFAULT_DB).toString();
    QString hostname = settings.value(dbconst::hostname, dbconst::DEFAULT_HOST).toString();
    qint16 port = settings.value(dbconst::port, dbconst::DEFAULT_PORT).toInt();

    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(dbname);
    db.setUserName(username);
    db.setPassword(password);

    if (db.open()) {
        QSqlQuery query;
        query.prepare(dbconst::SELECT_USERS);
        query.exec();
        while (query.next()) {
            if (username == query.value("name").toString()) {
                this->accept();
                return;
            }
        }
        db.close();
        showDialogError(this, "ERRORE", "l'untente non è autorizzato");
    }
    else {
        showDialogError(this, "ERRORE", "errore di autentificazione", db.lastError().text());
        ui->le_username->clear();
        ui->le_password->clear();
        ui->le_username->setFocus();
    }
}

void LoginDialog::openConfigDialog(void)
{
    qDebug() << "LoginDialog::openConfigDialog()";
    ConnectionSetupDialog dlg(this);
    dlg.exec();
}
