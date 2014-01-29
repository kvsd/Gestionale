#ifndef TABLESETUPDIALOG_H
#define TABLESETUPDIALOG_H

#include "libs/error.h"

#include <QDialog>
#include <QDebug>
#include <QInputDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class TableSetupDialog;
}

class TableSetupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TableSetupDialog(QWidget *parent = 0);
    ~TableSetupDialog();

private:
    Ui::TableSetupDialog *ui;

    QSqlQueryModel *model;
    QString currentTable;
    QHash<QString, QString> mapTables;

public slots:
    void changeTable(QString tbname);
    void addRecord(void);
    void removeRecord(void);
    void updateRecord(void);
    void updateView(void);
};

#endif // TABLESETUPDIALOG_H
