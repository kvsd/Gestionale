#ifndef PRIMANOTAWINDOW_H
#define PRIMANOTAWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QShowEvent>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSettings>

#include "primanota_const.h"
#include "primanotamodel.h"
#include "primanotaadddlg.h"
#include "libs/error.h"

namespace Ui {
class PrimaNotaWindow;
}

class PrimaNotaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PrimaNotaWindow(QWidget *parent = 0);
    ~PrimaNotaWindow();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

private:
    Ui::PrimaNotaWindow *ui;
    QSettings settings;
    PrimaNotaModel *primaNotaModel;

    void initModel();
    void initComboBox();
    void getInfoLabel();
    QString prepareFilterQuery();

public slots:
    void addNote();
    void updateNote();
    void removeNote();
    void updateViewNote();
};

#endif // PRIMANOTAWINDOW_H
