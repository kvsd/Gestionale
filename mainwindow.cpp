#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDriver>

const QString DEFAULT_USER = "user";
const QString DEFAULT_HOST = "localhost";
const int DEFAULT_PORT = 5432;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QPSQL");
    launchLoginDlg();
    this->setGeometry(settings.value("MainWindow.size", QRect(0, 0, 500, 350)).toRect());
    anagraficaMW = 0;
    magazzinoMW = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    settings.setValue("MainWindow.size", this->geometry());
}

void MainWindow::launchLoginDlg(void)
{
    db.close();

    LoginDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        ui->db_name->setText("Nessuno");
        ui->db_status->setText("Non connesso");
        ui->db_user->setText("Nessuno");
        ui->agentiButton->setDisabled(true);
        ui->clnFrnButton->setDisabled(true);
        ui->magazzinoButton->setDisabled(true);
        ui->actionSetup_Table->setDisabled(true);
        ui->actionConfigura_Azienda->setDisabled(true);
        this->setToolTip("Login non effettuato. E possibile effettuare il login dal menu Database");
        return;
    }

    QString dbname = settings.value("dbname", DEFAULT_USER).toString();
    QString hostname = settings.value("hostname", DEFAULT_HOST).toString();
    qint16 port = settings.value("port", DEFAULT_PORT).toInt();

    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(dbname);
    db.setUserName(dlg.getUsername());
    db.setPassword(dlg.getPassword());
    ui->db_user->setText(dlg.getUsername());
    ui->db_name->setText(dbname);

    if (db.open()) {
        ui->db_status->setText("Connesso");
        ui->agentiButton->setEnabled(true);
        ui->clnFrnButton->setEnabled(true);
        ui->magazzinoButton->setEnabled(true);
        ui->actionSetup_Table->setEnabled(true);
        ui->actionConfigura_Azienda->setEnabled(true);
        this->setToolTip("");
    }
    else {
        ui->db_user->setText("Nessuno");
        ui->db_name->setText("Nessuno");
        ui->db_status->setText("Non Connesso");
        showDialogError(this, ERR000, MSG000, db.lastError().text()); //NOTE codice errore 000
    }
}

void MainWindow::launchConnectionSetupDlg(void)
{
    ConnectionSetupDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    launchLoginDlg();
}

void MainWindow::launchTableSetupDlg(void)
{
    TableSetupDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchAgentiViewDlg(void)
{
    AgentiViewDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchAnagraficaDlg(void)
{
    if (anagraficaMW == 0) {
        anagraficaMW = new anagraficaWindow(this);
    }
    this->hide();
    anagraficaMW->show();
    anagraficaMW->updateViewAnagrafica();
}

void MainWindow::launchAziendaDlg(void)
{
    AziendaDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchMagazzinoDlg(void)
{
    //WORKINPROGRESS

    if (magazzinoMW == 0) {
        magazzinoMW = new MagazzinoWindow(this);
    }
    this->hide();
    magazzinoMW->show();
}
