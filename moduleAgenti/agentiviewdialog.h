#ifndef AGENTIVIEWDIALOG_H
#define AGENTIVIEWDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QSettings>
#include <QCloseEvent>
#include <QSqlRecord>

#include <moduleAgenti/agentiadddialog.h>
#include "libs/error.h"
#include "agenti_const.h"

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
    QSqlQueryModel *m_modelAgenti;
    QSettings m_settings;

protected:
    void closeEvent(QCloseEvent *);

public slots:
    void addRecord(void);
    void updateRecord(void);
    void removeRecord(void);
    void searchRecord();
    void updateViewAgenti(void);
};

#endif // AGENTIVIEWDIALOG_H
