#include "customwindow.h"

CustomWindow::CustomWindow(QWidget *parent)
    : QMainWindow(parent)
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

QString CustomWindow::winKeyStr = "%1.geometry";
QString CustomWindow::splitterKeyStr = "%1.%2.geometry";
QString CustomWindow::headerKeyStr = "%1.%2.headers";

void CustomWindow::saveWindowGeometry()
{
    qDebug() << objectName()+"::saveWindowGeometry() *";
    //Salvo la dimensione della finestra
    QString winKey = winKeyStr.arg(objectName());
    settings.setValue(winKey, this->geometry());
}

void CustomWindow::loadWindowGeometry()
{
    qDebug() << objectName()+"::loadWindowGeometry() *";
    //Carico la dimensione della finestra
    QString winKey = winKeyStr.arg(objectName());
    QRect winRect = settings.value(winKey, QRect(0,0,640,480)).toRect();
    setGeometry(winRect);
}

void CustomWindow::saveSplittersState()
{
    qDebug() << objectName() + "::saveSplittersState() *";
    //Salvo se presenti la posizione degli splitter della finestra
    QList <QSplitter *> list = findChildren<QSplitter *> ();
    for (auto splitter : list) {
        QString key = splitterKeyStr.arg(objectName(), splitter->objectName());
        settings.setValue(key, splitter->saveState());
    }
}

void CustomWindow::loadSplittersState()
{
    qDebug() << objectName() + "::loadSplittersState() *";
    //Carico se presenti la posizione degli splitter della finestra
    QList <QSplitter *> list = findChildren<QSplitter *> ();
    for (auto splitter : list) {
        QString key = splitterKeyStr.arg(objectName(), splitter->objectName());
        QByteArray state = settings.value(key).toByteArray();
        splitter->restoreState(state);
    }
}

void CustomWindow::saveTableViewSettings()
{
    qDebug() << objectName() + "::saveTableViewSettings() *";
    //Salvo se presenti lo stato degli Header delle tableview
    QList <QTableView *> list = findChildren<QTableView *>();
    for (auto view : list) {
        QString key = headerKeyStr.arg(objectName(), view->objectName());
        settings.setValue(key, view->horizontalHeader()->saveState());
    }
}

void CustomWindow::loadTableViewSettings()
{
    qDebug() << objectName() + "::loadTableViewSettings() *";
    //Carico se presenti lo stato degli Header delle tableview
    QList <QTableView *> list = findChildren<QTableView *>();
    for (auto view : list) {
        QString key = headerKeyStr.arg(objectName(), view->objectName());
        view->horizontalHeader()->setSectionsMovable(true);
        if (settings.contains(key)) {
            QByteArray array = settings.value(key).toByteArray();
            view->horizontalHeader()->restoreState(array);
        }
    }
}
