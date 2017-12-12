#ifndef REPORT_CONST_H
#define REPORT_CONST_H

#include "magazzino_const.h"
#include <QString>
#include <QRect>
#include <QMap>

namespace report {

    //SETTINGS
    const QString listinoCols = "Listino.cols";
    const QString ordineCols = "Ordine.cols";

    //Select utilizzata per la stampa dell'inventario
    const QString SELECT_INVENTARIO = "SELECT * FROM vw_inventario WHERE \"Quantità\"!=0";

    //Select che ritorna il totale dell'inventario, usato insieme alla query SELECT_INVENTARIO
    const QString SQL_INVENTARIO_TOT =
            QString::fromUtf8("SELECT sum(\"SubTotale\") AS \"Totale\" "
                              "FROM vw_inventario");

    //Select utilizzata per la stampa degli ordini
    const QString SELECT_ORDINE = magazzino::SELECT_ARTICOLI_ALL +
            QString::fromUtf8(" AND an.rag_sociale = '%1'");

    const QString LISTINO = "Listino";
    const QString INVENTARIO = "Inventario";
    const QString ORDINE = "Ordine";

        //CMP Nome Campo Tabella sql
        const QString CMP_ID      = "Id";
        const QString CMP_DESCR   = "Descrizione";
        const QString CMP_FORNIT  = "Fornitore";
        const QString CMP_MARCA   = "Marca";
        const QString CMP_MODELLO = "Modello";
        const QString CMP_COD_ART = "Cod.Articolo";
        const QString CMP_COD_FOR = "Cod.Fornitore";
        const QString CMP_COD_EAN = "Cod.EAN";
        const QString CMP_MERCE   = "Cat.Merce";
        const QString CMP_COD_IVA = "Cod.IVA";
        const QString CMP_UM      = "UM";
        const QString CMP_SCORTA  = "Scorta Minima";
        const QString CMP_QT      = QString::fromUtf8("Quantità");
        const QString CMP_PRZ_FAT = "Prezzo Fattura";
        const QString CMP_SCONTO  = "Sconto Fornitore";
        const QString CMP_PRZ_ACQ = "Prezzo Acquisto";
        const QString CMP_RICAR   = "Ricarico";
        const QString CMP_IVA     = "Iva";
        const QString CMP_PRZ_FIN = "Prezzo Finito";
        const QString CMP_PRZ_VEN = QString::fromUtf8("Prezzo Vendità");
        const QString CMP_FATTURA = "Nr.Fattura";
        const QString CMP_DATA    = "Data Arrivo";
        const QString CMP_SEDE    = "Sede Magazzino";
        const QString CMP_NOTE    = "Note";
        const QString CMP_ID_ART  = "Id Articolo";
        const QString CMP_SUBTOT = "SubTotale";

}
#endif // REPORT_CONST_H
