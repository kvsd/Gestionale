#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "libs/error.h"
#include "moduleDatabase/logindialog.h"
#include "moduleDatabase/connectionsetupdialog.h"
#include "moduleDatabase/tablesetupdialog.h"
#include "moduleAgenti/agentiviewdialog.h"
#include "moduleAnagrafica/anagraficawindow.h"
#include "moduleAzienda/aziendadialog.h"
#include "moduleMagazzino/magazzinowindow.h"
#include "modulePrimaNota/primanotawindow.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSettings settings;
    AnagraficaWindow *anagraficaMW;
    MagazzinoWindow *magazzinoMW;
    PrimaNotaWindow *primaNotaMW;
    void diplayInfo(void);
    void setEnabledControl(bool value);

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void launchLoginDlg(void);
    void launchConnectionSetupDlg(void);
    void launchTableSetupDlg(void);
    void launchAgentiViewDlg(void);
    void launchAnagraficaDlg(void);
    void launchAziendaDlg(void);
    void launchMagazzinoDlg(void);
    void launchPrimaNotaDlg(void);
};

#endif // MAINWINDOW_H
