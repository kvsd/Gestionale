#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <connectionsetupdialog.h>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    QString getUsername() const;
    QString getPassword() const;

private:
    Ui::LoginDialog *ui;
    QString username;
    QString password;

public slots:
    void connectToDatabase(void);
    void openConfigDialog(void);
};

#endif // LOGINDIALOG_H
