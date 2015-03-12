#include "connectionsetupdialog.h"
#include "ui_connectionsetupdialog.h"

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
    QString dbname = settings.value(dbconst::dbname, dbconst::DEFAULT_DB).toString();
    QString hostname = settings.value(dbconst::hostname, dbconst::DEFAULT_HOST).toString();
    qint16 port = settings.value(dbconst::port, dbconst::DEFAULT_PORT).toInt();

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

    settings.setValue(dbconst::dbname, dbname);
    settings.setValue(dbconst::hostname, hostname);
    settings.setValue(dbconst::port, port);
}
