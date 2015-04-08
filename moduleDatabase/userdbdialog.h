#ifndef USERDBDIALOG_H
#define USERDBDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>
#include <QDebug>

#include "libs/error.h"

namespace Ui {
class UserDbDialog;
}

class UserDbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDbDialog(QWidget *parent = 0);
    ~UserDbDialog();

private:
    Ui::UserDbDialog *ui;
    QSqlQueryModel *modelUserList;
    void initModel();
    void updateModel();
    bool isUserExists(QString username);
    bool isUserInGroup(QString username);
    bool isUserIsAuth(QString username);

    bool createUser(QString username, QString password);
    bool authorizedUser(QString username);

public slots:
    void userAdd(void);
    void userMod(void);
    void userDel(void);
};

#endif // USERDBDIALOG_H
