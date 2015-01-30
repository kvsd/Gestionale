#ifndef UTILS
#define UTILS

#include "libs/error.h"
#include <QDebug>
#include <QMap>
#include <QSqlQueryModel>
#include <QLocale>

QMap<int,QString> prepareMapsFromModel(QSqlQueryModel *model);
double stringToDouble(QString string);

#endif // UTILS

