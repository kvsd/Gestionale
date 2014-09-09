#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Test");
    QCoreApplication::setApplicationName("Gestionale");
    QLocale::setDefault(QLocale(QLocale::Italian, QLocale::Italy));
    MainWindow w;
    w.show();
    
    return a.exec();
}
