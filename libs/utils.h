#ifndef UTILS
#define UTILS

#include <QDebug>
#include <QMap>
#include <QSqlQueryModel>

QMap<int,QString> prepareMapsFromModel(QSqlQueryModel *model);

#endif // UTILS

