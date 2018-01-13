#ifndef MAGAZZINOWINDOW_H
#define MAGAZZINOWINDOW_H

#include "libs/custommodel.h"
#include "libs/gestionale_const.h"
#include "libs/utils.h"
#include "libs/customwindow.h"
#include "articolodialog.h"
#include "optionsmagazzinodialog.h"
#include "magazzino_const.h"
#include "codivaupdatedialog.h"
#include "configprintdialog.h"
#include "moduleReport/listinodlg.h"

#include <QSqlQueryModel>
#include <QMap>
#include <QDebug>
#include <QCloseEvent>
#include <QSqlRecord>
#include <QSqlField>
#include <QTableView>

namespace Ui {
class MagazzinoWindow;
}

class MagazzinoWindow : public CustomWindow
{
    Q_OBJECT

public:
    explicit MagazzinoWindow(QWidget *parent = 0);
    ~MagazzinoWindow();

private:
    Ui::MagazzinoWindow *ui;
    CustomModel *articoloModel;
    CustomModel *storicoModel;
    QSqlQueryModel *fornitoreModel;
    QSqlTableModel *categoriaModel;
    QSqlTableModel *marcaModel;
    QSqlTableModel *sedeModel;
    QSettings m_settings;

    void initModel();
    void initComboBox();
    void updateModel();
    void loadConfigSettings();
    void saveConfigSettings();
    QString searchString();
    QString filterString();
    QString giacenzaString();
    QString orderString();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

public slots:
    void addRecord();
    void updateRecord();
    void cloneRecord();
    void removeRecord();
    void updateViewMagazzino(void);
    void updateViewStorico(QModelIndex index);
    void openConfigDialog(void);
    void changeCodIva(void);
    void launchReportConfig(void);
    void launchReportListino(void);
    void launchReportInventario(void);
    void findCodBarre(void);
};

#endif // MAGAZZINOWINDOW_H
