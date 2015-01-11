#include <QApplication>
#include "mainwindow.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Test");
    QCoreApplication::setApplicationName("Gestionale");
    QLocale::setDefault(QLocale(QLocale::Italian, QLocale::Italy));

    LoginDialog dlg;
    bool ok = dlg.exec();

    if (ok == QDialog::Rejected) {
        return 1;
    }

    MainWindow w;
    w.show();
    
    return a.exec();
}
