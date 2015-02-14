#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow()";
    ui->setupUi(this);
    db = QSqlDatabase::database();
    diplayInfo();

    this->setGeometry(settings.value("MainWindow.size", QRect(0, 0, 500, 350)).toRect());
    anagraficaMW = 0;
    magazzinoMW = 0;
    primaNotaMW = 0;
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

void MainWindow::launchLoginDlg(void)
{
    qDebug() << "MainWindow::launchLoginDlg()";

    LoginDialog dlg(this);
    dlg.exec();
    diplayInfo();
}

void MainWindow::diplayInfo(void)
{
    qDebug() << "MainWindow::diplayInfo()";

    if (db.open()) {
        ui->db_user->setText(db.userName());
        ui->db_name->setText(db.databaseName());
        ui->db_status->setText("Connesso");
        ui->agentiButton->setEnabled(true);
        ui->clnFrnButton->setEnabled(true);
        ui->magazzinoButton->setEnabled(true);
        ui->actionSetup_Table->setEnabled(true);
        ui->actionConfigura_Azienda->setEnabled(true);
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

void MainWindow::launchPrimaNotaDlg(void)
{
    qDebug() << "MainWindow::launchPrimaNotaDlg()";

    if (primaNotaMW == 0) {
        primaNotaMW = new PrimaNotaWindow(this);
    }
    this->hide();
    primaNotaMW->move(this->pos());
    primaNotaMW->show();
}
