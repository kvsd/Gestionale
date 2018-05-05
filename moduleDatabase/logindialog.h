#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>

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
    QSqlDatabase m_db;
    QString m_username;
    QString m_password;
    QSettings m_settings;
    bool isAuthorizedUser(QString user) const;

public slots:
    void connectToDatabase(void);
    void openConfigDialog(void);
};

#endif // LOGINDIALOG_H
