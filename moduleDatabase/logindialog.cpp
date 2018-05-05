#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    qDebug() << "LoginDialog()";
    ui->setupUi(this);

    if (m_db.contains())
        m_db = QSqlDatabase::database();
    else
        m_db = QSqlDatabase::addDatabase("QPSQL");
}

LoginDialog::~LoginDialog()
{
    qDebug() << "~LoginDialog()";
    delete ui;
}

bool LoginDialog::isAuthorizedUser(QString user) const
{
    //Controlla se user e' presente nella tabella user_db
    qDebug() << "LoginDialog::isAuthorizedUser()";

    QSqlQuery query;
    query.prepare(dbconst::SELECT_USERS);
    query.exec();
    while (query.next()) {
        if (user == query.value("name").toString() || user == "postgres")
            return true;
    }
    return false;
}

void LoginDialog::connectToDatabase(void)
{
    qDebug() << "LoginDialog::connectToDatabase()";

    m_username = ui->le_username->text();
    m_password = ui->le_password->text();
    QString dbname = m_settings.value(dbconst::dbname, dbconst::DEFAULT_DB).toString();
    QString hostname = m_settings.value(dbconst::hostname, dbconst::DEFAULT_HOST).toString();
    qint16 port = m_settings.value(dbconst::port, dbconst::DEFAULT_PORT).toInt();

    m_db.setHostName(hostname);
    m_db.setPort(port);
    m_db.setDatabaseName(dbname);
    m_db.setUserName(m_username);
    m_db.setPassword(m_password);

    if (m_db.open()) {
        if (isAuthorizedUser(m_username))
            this->accept();
        else {
            m_db.close();
            showDialogError(this, "ERRORE", "l'untente non è autorizzato");
        }
    }
    else {
        showDialogError(this, "ERRORE", "errore di autentificazione", m_db.lastError().text());
        ui->le_password->clear();
        ui->le_password->setFocus();
    }
}

void LoginDialog::openConfigDialog(void)
{
    qDebug() << "LoginDialog::openConfigDialog()";
    ConnectionSetupDialog dlg(this);
    dlg.exec();
}
