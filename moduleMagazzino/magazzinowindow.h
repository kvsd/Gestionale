#ifndef MAGAZZINOWINDOW_H
#define MAGAZZINOWINDOW_H

#include "articolodialog.h"

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QMap>
#include <QDebug>

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
    QSqlQueryModel *magazzinoModel;
    QSqlQueryModel *selectionModel;
    QSqlQueryModel *storicoModel;

    QString id_fornitore;
    QMap <QString, QString> filterMap;


protected:
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

public slots:
    void updateTableMagazzino(void);
    void updateFilterValue(QString s);
    void addRecord();
    void updateRecord();
    void removeRecord();
    void updateStoricoView(QModelIndex index);
    void fastSearch();
};

#endif // MAGAZZINOWINDOW_H
