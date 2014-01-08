#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "error.h"
#include "logindialog.h"
#include "connectionsetupdialog.h"
#include "tablesetupdialog.h"
#include "moduleAgenti/agentiviewdialog.h"
#include "moduleAnagrafica/anagraficawindow.h"
#include "moduleAzienda/aziendadialog.h"
#include "moduleMagazzino/magazzinowindow.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>

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
    anagraficaWindow *anagraficaMW;
    MagazzinoWindow *magazzinoMW;


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
};

#endif // MAINWINDOW_H
