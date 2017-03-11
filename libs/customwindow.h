#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSettings>
#include <QDebug>

class CustomWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CustomWindow(QWidget *parent = 0);

protected:
    QSettings settings;

    void loadColumnVisibility(QTableView *view, QString groupSettings);
    QMap<QString, QBrush> getBgSettings(QString groupName);

private:

signals:

public slots:
};

#endif // CUSTOMWINDOW_H
