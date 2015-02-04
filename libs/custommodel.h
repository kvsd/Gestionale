#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QSqlQueryModel>
#include <QMap>
#include <QColor>
#include <QBrush>
#include <QSettings>

class CustomModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CustomModel(QString colsGroup, QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
    void loadSettings();

private:
    QMap<int, QBrush>colorsMaps;
    QString group;
    QSettings settings;

    void prepareMap(void);

signals:

public slots:

};

#endif // CUSTOMMODEL_H
