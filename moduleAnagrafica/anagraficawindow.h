#ifndef ANAGRAFICAWINDOW_H
#define ANAGRAFICAWINDOW_H

#include "moduleAnagrafica/anagraficaadddialog.h"
#include "moduleAnagrafica/optionsanagraficadialog.h"
#include "libs/custommodel.h"
#include "anagrafica_const.h"

#include <QMainWindow>
#include <QDialog>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSettings>
#include <QCloseEvent>
#include <QShowEvent>

namespace Ui {
class anagraficaWindow;
}

class anagraficaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit anagraficaWindow(QWidget *parent = 0);
    ~anagraficaWindow();

private:
    Ui::anagraficaWindow *ui;
    CustomModel *anagraficaModel;
    QSettings settings;
    QString str_search;
    void loadConfigSettings();
    void saveConfigSettings();

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

public slots:
    void addRecord(void);
    void updateRecord(void);
    void removeRecord(void);
    void searchRecord(void);
    void updateViewAnagrafica(void);
    void openConfigDialog(void);
    void updateStringSearch(void);

};

#endif // ANAGRAFICAWINDOW_H
