#ifndef MAGAZZINOWINDOW_H
#define MAGAZZINOWINDOW_H

#include "libs/custommodel.h"
#include "libs/gestionale_const.h"
#include "articolodialog.h"
#include "optionsmagazzinodialog.h"

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QMap>
#include <QDebug>
#include <QCloseEvent>
#include <QFileDialog>
#include <QSqlRecord>

namespace Ui {
class MagazzinoWindow;
}

class MagazzinoWindow : public QMainWindow
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
    QSettings settings;

    void initModel();
    void updateModel();
    void loadConfigSettings();
    void saveConfigSettings();
    QString searchString();
    QString filterString();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *);

public slots:
    void addRecord();
    void updateRecord();
    void removeRecord();
    void updateViewMagazzino(void);
    void updateViewStorico(QModelIndex index);
    void openConfigDialog(void);
    void exportMagazzinoCsv(void);
    void exportStoricoCsv(void);
};

#endif // MAGAZZINOWINDOW_H
