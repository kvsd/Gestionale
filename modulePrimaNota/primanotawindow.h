#ifndef PRIMANOTAWINDOW_H
#define PRIMANOTAWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSqlQueryModel>
#include <QDebug>

#include "primanota_const.h"

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

private:
    Ui::PrimaNotaWindow *ui;
    QSqlQueryModel *primaNotaModel;

public slots:
    void addNote();
    void updateNote();
    void removeNote();
};

#endif // PRIMANOTAWINDOW_H
