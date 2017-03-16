#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QSettings>
#include <QDebug>
#include <QSplitter>
#include <QHeaderView>

class CustomWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CustomWindow(QWidget *parent = 0);

protected:
    QSettings settings;

    void loadColumnVisibility(QTableView *view, QString groupSettings);
    QMap<QString, QBrush> getBgSettings(QString groupName);

    void saveWindowGeometry();
    void loadWindowGeometry();

    void saveSplittersState();
    void loadSplittersState();

    void saveTableViewSettings();
    void loadTableViewSettings();

private:
    static QString winKeyStr;
    static QString splitterKeyStr;
    static QString headerKeyStr;

signals:

public slots:
};

#endif // CUSTOMWINDOW_H
