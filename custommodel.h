#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QSqlQueryModel>
#include <QMap>
#include <QColor>
#include <QBrush>


class CustomModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;

private:
    QMap<int, QColor>colors;

signals:

public slots:

};

#endif // CUSTOMMODEL_H
