#include "utils.h"

QMap<int,QString> prepareMapsFromModel(QSqlQueryModel *model)
{
    /* Ritorna una mappa <int,QString> con la posizione e il nome delle colonne
    ** del model passato come argomento */
    qDebug() << "magazzino::prepapreMapsFromModel()";

    QMap <int,QString> mapNameCols;

    int nrCols = model->columnCount();
    for (int i=0; i<nrCols; i++) {
        mapNameCols[i] = model->headerData(i, Qt::Horizontal).toString();
    }

    return mapNameCols;
}

