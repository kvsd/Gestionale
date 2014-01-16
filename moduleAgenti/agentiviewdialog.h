#ifndef AGENTIVIEWDIALOG_H
#define AGENTIVIEWDIALOG_H

#include <moduleAgenti/agentiadddialog.h>
#include "error.h"
#include "utils/enum_const.h"

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QSettings>
#include <QCloseEvent>

namespace Ui {
class AgentiViewDialog;
}

class AgentiViewDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AgentiViewDialog(QWidget *parent = 0);
    ~AgentiViewDialog();
    
private:
    Ui::AgentiViewDialog *ui;
    QSqlQueryModel *modelAgenti;
    QSettings settings;

protected:
    void closeEvent(QCloseEvent *);

public slots:
    void addRecord(void);
    void updateRecord(void);
    void removeRecord(void);
    void searchRecord(QString s);
    void updateTable(void);

};

#endif // AGENTIVIEWDIALOG_H
