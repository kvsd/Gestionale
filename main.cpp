#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Test");
    QCoreApplication::setApplicationName("Gestionale");

    MainWindow w;
    w.show();
    
    return a.exec();
}
