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
    anagraficaMW = nullptr;
    magazzinoMW = nullptr;
    primaNotaMW = nullptr;
    documentiMW = nullptr;
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
    //Visualizza nelle label del groupbox Info i dati della connessione. E in
    //base allo stato del database abilita/disabilita i controlli dell'interfaccia

    qDebug() << "MainWindow::diplayInfo()";

    if (db.isOpen()) {
        ui->db_user->setText(db.userName());
        ui->db_name->setText(db.databaseName());
        ui->db_status->setText("Connesso");
        if (db.userName() == "postgres")
            setEnabledControl(false);
        else
            setEnabledControl(true);
    }
    else {
        ui->db_user->setText("Nessuno");
        ui->db_name->setText("Nessuno");
        ui->db_status->setText("Non Connesso");
        setEnabledControl(false);
    }
}

void MainWindow::setEnabledControl(bool value)
{
    //Abilita o disabilita tutti i controlli dell'interfaccia.
    qDebug() << "MainWindow::setEnabledControl()";

    ui->agentiButton->setEnabled(value);
    ui->clnFrnButton->setEnabled(value);
    ui->magazzinoButton->setEnabled(value);
    ui->primaNotaButton->setEnabled(value);
    ui->documentiButton->setEnabled(value);
    ui->actionSetup_Table->setEnabled(value);
    ui->actionConfigura_Azienda->setEnabled(value);
}

void MainWindow::launchConnectionSetupDlg(void)
{
    qDebug() << "MainWindow::launchConnectionSetupDlg()";
    ConnectionSetupDialog dlg(this);
    bool ok = dlg.exec();
    if (!ok)
        return;

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
    if (anagraficaMW == nullptr)
        anagraficaMW = new AnagraficaWindow(this);

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
    if (magazzinoMW == nullptr)
        magazzinoMW = new MagazzinoWindow(this);

    this->hide();
    magazzinoMW->move(this->pos());
    magazzinoMW->show();
}

void MainWindow::launchPrimaNotaDlg(void)
{
    qDebug() << "MainWindow::launchPrimaNotaDlg()";

    if (primaNotaMW == nullptr)
        primaNotaMW = new PrimaNotaWindow(this);

    this->hide();
    primaNotaMW->move(this->pos());
    primaNotaMW->show();
}

void MainWindow::launchUserDlg(void)
{
    qDebug() << "MainWindow::launchUserDlg()";

    if (!db.isOpen()) {
        showDialogError(this, ERR054, MSG026); //NOTE codice errore 054
        return;
    }

    if (db.userName()!= "postgres") {
        showDialogError(this, ERR055, MSG027); //NOTE codice errore 055
        return;
    }

    UserDbDialog dlg(this);
    dlg.exec();
}

void MainWindow::launchDocumentiDlg(void)
{
    qDebug() << "MainWindow::launchDocumentiDlg()";
    if (documentiMW == nullptr)
        documentiMW = new DocumentiWindow(this);

    this->hide();
    documentiMW->move(this->pos());
    documentiMW->show();
}
