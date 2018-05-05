#ifndef TABLESETUPDIALOG_H
#define TABLESETUPDIALOG_H

#include "libs/error.h"
#include "libs/gestionale_const.h"

#include <QDialog>
#include <QDebug>
#include <QInputDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringListModel>

namespace Ui {
class TableSetupDialog;
}

class TableSetupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TableSetupDialog(QWidget *parent = 0);
    ~TableSetupDialog();
    enum columns {ID, DESCR};

private:
    Ui::TableSetupDialog *ui;

    QSqlQueryModel *m_model;
    QString m_currentTable;
    QHash<QString, QString> m_mapTables;
    QStringListModel *m_tableModel;

public slots:
    void changeTable(QString tbname);
    void addRecord(void);
    void removeRecord(void);
    void updateRecord(void);
    void updateView(void);
};

#endif // TABLESETUPDIALOG_H
