#ifndef UTILS
#define UTILS

#include "libs/error.h"
#include <QDebug>
#include <QMap>
#include <QSqlQueryModel>
#include <QLocale>
#include <QString>

const int LENGHT_COD_FISCALE = 16;
const int LENGHT_PAR_IVA = 11;
const int CHECKDIGIT_PIVA = 10;
const int CHECKDIGIT_CF = 15;

QMap<int,QString> prepareMapsFromModel(QSqlQueryModel *model);

double stringToDouble(QString string);

bool controlloPartitaIva(QString s);

bool controlloCodiceFiscale(QString s);

#endif // UTILS

