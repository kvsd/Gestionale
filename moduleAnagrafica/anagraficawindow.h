#ifndef ANAGRAFICAWINDOW_H
#define ANAGRAFICAWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDebug>
#include <QSettings>
#include <QCloseEvent>
#include <QShowEvent>
#include <QTableView>

#include "moduleAnagrafica/anagraficaadddialog.h"
#include "moduleAnagrafica/optionsanagraficadialog.h"
#include "libs/custommodel.h"
#include "libs/customwindow.h"
#include "anagrafica_const.h"

namespace Ui {
class AnagraficaWindow;
}

class AnagraficaWindow : public CustomWindow
{
    Q_OBJECT

public:
    explicit AnagraficaWindow(QWidget *parent = 0);
    ~AnagraficaWindow();

private:
    Ui::AnagraficaWindow *ui;
    CustomModel *m_anagraficaModel;
    QSqlTableModel *m_cittaModel;
    QSqlTableModel *m_provinciaModel;
    QSqlTableModel *m_statoModel;
    QSqlTableModel *m_agenteModel;

    void initModel();
    void updateModel();
    void initComboBox();
    void loadConfigSettings();
    void saveConfigSettings();
    QString getSearchString();
    QString getFilterString1();
    QString getFilterString2();

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

public slots:
    void addRecord(void);
    void updateRecord(void);
    void removeRecord(void);
    void updateViewAnagrafica(void);
    void openConfigDialog(void);

};

#endif // ANAGRAFICAWINDOW_H
