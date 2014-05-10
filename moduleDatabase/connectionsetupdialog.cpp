#include "connectionsetupdialog.h"
#include "ui_connectionsetupdialog.h"

const QString DEFAULT_DBNAME = "user";
const QString DEFAULT_HOSTNAME = "localhost";
const int DEFAULT_PORT = 5432;

ConnectionSetupDialog::ConnectionSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSetupDialog)
{
    qDebug() << "ConnectionSetupDialog()";
    ui->setupUi(this);
    loadSettings();
}

ConnectionSetupDialog::~ConnectionSetupDialog()
{
    qDebug() << "~ConnectionSetupDialog()";
    delete ui;
}

void ConnectionSetupDialog::loadSettings(void)
{
    qDebug() << "ConnectionSetupDialog::loadSettings()";
    QString dbname = settings.value("dbname", DEFAULT_DBNAME).toString();
    QString hostname = settings.value("hostname", DEFAULT_HOSTNAME).toString();
    qint16 port = settings.value("port", DEFAULT_PORT).toInt();

    ui->le_dbname->setText(dbname);
    ui->le_hostname->setText(hostname);
    ui->le_port->setValue(port);
}

void ConnectionSetupDialog::saveSettings(void)
{
    qDebug() << "ConnectionSetupDialog::saveSettings()";
    QString dbname = ui->le_dbname->text();
    QString hostname = ui->le_hostname->text();
    qint16 port = ui->le_port->value();

    settings.setValue("dbname", dbname);
    settings.setValue("hostname", hostname);
    settings.setValue("port", port);
}
