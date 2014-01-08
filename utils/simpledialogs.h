#ifndef SIMPLEDIALOGS_H
#define SIMPLEDIALOGS_H

#include "error.h"

#include <QString>
#include <QInputDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>

const QString ADD_DITTA_QUERY = "INSERT INTO tipo_ditta(descr) VALUES(:value)";
const QString ADD_CITTA_QUERY = "INSERT INTO citta(descr) VALUES(:value)";
const QString ADD_PROVINCIA_QUERY = "INSERT INTO provincia(descr) VALUES(:value)";
const QString ADD_CAP_QUERY = "INSERT INTO cap(descr) VALUES(:value)";
const QString ADD_STATO_QUERY = "INSERT INTO stato(descr) VALUES(:value)";

void allDlg(QWidget *parent=0, QSqlTableModel *model=0, QString strquery="", const char *title="", QString error_nr="");

#endif // SIMPLEDIALOGS_H
