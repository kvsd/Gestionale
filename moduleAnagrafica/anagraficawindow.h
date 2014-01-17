#ifndef ANAGRAFICAWINDOW_H
#define ANAGRAFICAWINDOW_H

#include "moduleAnagrafica/anagraficaadddialog.h"
#include "moduleAnagrafica/optionsanagraficadialog.h"
#include "utils/enum_const.h"
#include "custommodel.h"

#include <QMainWindow>
#include <QDialog>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSettings>
#include <QCloseEvent>

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
    void loadConfigSettings();
    QString str_search;

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void addRecord(void);
    void updateRecord(void);
    void removeRecord(void);
    void searchRecord(QString s);
    void openConfigDialog(void);
    void modifyStringSearch(void);

public slots:
    void updateTable(void);
};

#endif // ANAGRAFICAWINDOW_H
