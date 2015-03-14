#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "connectionsetupdialog.h"
#include "libs/error.h"
#include "db_const.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QSqlDatabase db;
    QString username;
    QString password;
    QSettings settings;
    bool isAuthorizedUser(QString user) const;

public slots:
    void connectToDatabase(void);
    void openConfigDialog(void);
};

#endif // LOGINDIALOG_H
