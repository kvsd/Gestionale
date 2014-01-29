#ifndef CONTROLLODATI_H
#define CONTROLLODATI_H

#include <QHash>
#include <QString>
#include <QDebug>

const int LENGHT_COD_FISCALE = 16;
const int LENGHT_PAR_IVA = 11;
const int CHECKDIGIT_PIVA = 10;
const int CHECKDIGIT_CF = 15;

bool controlloPartitaIva(QString s);
bool controlloCodiceFiscale(QString s);

#endif // CONTROLLODATI_H
