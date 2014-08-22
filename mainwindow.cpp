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
    qDebug() << "MainWindow()";
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QPSQL");
    while (int exitCode = launchLoginDlg()) {
        if (exitCode == 2) {
            delete ui;
            exit(0);
        }
    }

    this->setGeometry(settings.value("MainWindow.size", QRect(0, 0, 500, 350)).toRect());
    anagraficaMW = 0;
    magazzinoMW = 0;
}

MainWindow::~MainWindow()
{
    qDebug() << "~MainWindow()";
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent()";
    event->accept();
    settings.setValue("MainWindow.size", this->geometry());
}

int MainWindow::launchLoginDlg(void)
{
    qDebug() << "MainWindow::launchLoginDlg()";
    db.close();

    LoginDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return 2;
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
        return 0;
    }
    else {
        ui->db_user->setText("Nessuno");
        ui->db_name->setText("Nessuno");
        ui->db_status->setText("Non Connesso");
        ui->agentiButton->setEnabled(false);
        ui->clnFrnButton->setEnabled(false);
        ui->magazzinoButton->setEnabled(false);
        ui->actionSetup_Table->setEnabled(false);
        ui->actionConfigura_Azienda->setEnabled(false);
        showDialogError(this, ERR000, MSG000, db.lastError().text()); //NOTE codice errore 000
        return 1;
    }
}

void MainWindow::launchConnectionSetupDlg(void)
{
    qDebug() << "MainWindow::launchConnectionSetupDlg()";
    ConnectionSetupDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok) {
        return;
    }
    launchLoginDlg();
}

void MainWindow::launchTableSetupDlg(void)
{
    qDebug() << "MainWindow::launchTableSetupDlg()";
    TableSetupDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchAgentiViewDlg(void)
{
    qDebug() << "MainWindow::launchAgentiViewDlg()";
    AgentiViewDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchAnagraficaDlg(void)
{
    qDebug() << "MainWindow::launchAnagraficaDlg()";
    if (anagraficaMW == 0) {
        anagraficaMW = new AnagraficaWindow(this);
    }
    this->hide();
    anagraficaMW->move(this->pos());
    anagraficaMW->show();
}

void MainWindow::launchAziendaDlg(void)
{
    qDebug() << "MainWindow::launchAziendaDlg()";
    AziendaDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchMagazzinoDlg(void)
{
    qDebug() << "MainWindow::launchMagazzinoDlg()";
    //WORKINPROGRESS

    if (magazzinoMW == 0) {
        magazzinoMW = new MagazzinoWindow(this);
    }
    this->hide();
    magazzinoMW->move(this->pos());
    magazzinoMW->show();
}
