#include "customwindow.h"

CustomWindow::CustomWindow(QWidget *parent) : QMainWindow(parent)
{

}

void CustomWindow::loadColumnVisibility(QTableView *view, QString groupSettings)
{
    qDebug() << objectName() + "::loadColumnVisibility() *";
    settings.beginGroup(groupSettings);

    QStringList cols = settings.allKeys();
    if (!cols.isEmpty()) {
        for (auto i : cols) {
            int col = QVariant(i).toInt();
            bool value = settings.value(i).toBool();
            view->setColumnHidden(col, !value);
        }
    }
    settings.endGroup();
}

QMap<QString, QBrush> CustomWindow::getBgSettings(QString groupName)
{
    qDebug() << objectName() + "::getBgMap() *";
    QMap<QString, QBrush> map;
    settings.beginGroup(groupName);

    for (auto key : settings.allKeys()) {
        QString value = settings.value(key, "-1").toString();
        if (value != "-1")
            map[key] = QBrush(QColor(value));
    }

    settings.endGroup();
    return map;
}
