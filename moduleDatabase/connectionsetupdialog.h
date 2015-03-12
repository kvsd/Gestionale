#ifndef CONNECTIONSETUPDIALOG_H
#define CONNECTIONSETUPDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include "db_const.h"

namespace Ui {
class ConnectionSetupDialog;
}

class ConnectionSetupDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectionSetupDialog(QWidget *parent = 0);
    ~ConnectionSetupDialog();
    
private:
    Ui::ConnectionSetupDialog *ui;
    void loadSettings(void);
    QSettings settings;

public slots:
    void saveSettings(void);
};

#endif // CONNECTIONSETUPDIALOG_H
