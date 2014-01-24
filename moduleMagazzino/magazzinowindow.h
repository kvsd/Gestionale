#ifndef MAGAZZINOWINDOW_H
#define MAGAZZINOWINDOW_H

#include "articolodialog.h"
#include "optionsmagazzinodialog.h"
#include "../custommodel.h"

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QMap>
#include <QDebug>
#include <QCloseEvent>

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
    QSqlQueryModel *selectionModel;
    CustomModel *storicoModel;
    QSettings settings;

    QMap <QString, QString> filterMap;
    void loadConfigSettings();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *);

public slots:
    void addRecord();
    void updateRecord();
    void removeRecord();
    void updateFilterValue(QString s);
    void updateViewMagazzino(void);
    void updateViewStorico(QModelIndex index);
    void searchRecord();
    void openConfigDialog(void);
};

#endif // MAGAZZINOWINDOW_H
