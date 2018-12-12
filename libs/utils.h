#ifndef UTILS
#define UTILS

#include "libs/error.h"
#include <QDebug>
#include <QMap>
#include <QSqlQueryModel>
#include <QLocale>
#include <QString>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QComboBox>

const int LENGHT_COD_FISCALE = 16;
const int LENGHT_PAR_IVA = 11;
const int CHECKDIGIT_PIVA = 10;
const int CHECKDIGIT_CF = 15;

QMap<int,QString> prepareMapsFromModel(QSqlQueryModel *model);

QSqlTableModel * setupComboBox(QString tablename, QComboBox *cb, int viewCol);

void setValueCB(QComboBox *box, QString value, int searchCol);

double stringToDouble(QString string);

bool controlloPartitaIva(QString s);

bool controlloCodiceFiscale(QString s);

double setRicarico(double prezzo, QString ricarico);

double setSconto(double prezzo, QString sconto);

#endif // UTILS

