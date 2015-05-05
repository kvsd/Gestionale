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
    explicit CustomModel(QString colsGroup, Qt::AlignmentFlag textAlignment, QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
    void loadSettings();
    void setAlignMap(QMap <QString, Qt::AlignmentFlag> map);

private:
    QMap<int, QBrush>colorsMaps;
    QMap<QString, Qt::AlignmentFlag>alignMaps;
    QString group;
    QSettings settings;
    Qt::AlignmentFlag defaulTextAlign;

    void prepareMap(void);

signals:

public slots:

};

#endif // CUSTOMMODEL_H
