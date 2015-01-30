#include "utils.h"

QMap<int,QString> prepareMapsFromModel(QSqlQueryModel *model)
{
    /* Ritorna una mappa <int,QString> con la posizione e il nome delle colonne
    ** del model passato come argomento */
    qDebug() << "prepapreMapsFromModel()";

    QMap <int,QString> mapNameCols;

    int nrCols = model->columnCount();
    for (int i=0; i<nrCols; i++) {
        mapNameCols[i] = model->headerData(i, Qt::Horizontal).toString();
    }

    return mapNameCols;
}

double stringToDouble(QString string)
{
    /*Funzione che prova a convertire una stringa in un double. Se riesce a
    **convertire la stringa ritorna il double convertito, altrimenti ritorna
    **il varole 0.*/
    qDebug() << "stringToDouble()";
    if (string.isEmpty()) {
        return 0;
    }

    QString symbol = QLocale().currencySymbol();
    if (string.contains(symbol)) {
        string = string.replace(symbol, "");
    }

    bool ok = 0;
    double number = 0;
    number = string.toDouble(&ok);
    if (ok)
        return number;

    number = QLocale().toDouble(string, &ok);
    if (ok)
        return number;

    return 0;
}
