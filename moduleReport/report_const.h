#ifndef REPORT_CONST_H
#define REPORT_CONST_H

#include "magazzino_const.h"
#include <QString>

namespace report {
    //Select stampa listino da fattura
    const QString SELECT_LISTINO_FATTURA =
        QString::fromUtf8("SELECT DISTINCT ON (mg.id, mg.descr, ls.fattura) "
                          "mg.id As \"Id\", "
                          "mg.descr As \"Descrizione\", "
                          "an.rag_sociale AS \"Fornitore\", "
                          "mg.modello As \"Modello\", "
                          "mg.cod_articolo AS \"Cod.Articolo\", "
                          "mg.cod_fornitore AS \"Cod.Fornitore\", "
                          "mg.cod_barre AS \"Cod.EAN\", "
                          "format('%s%%', mg.cod_iva) AS \"Cod.IVA\", "
                          "mg.scorta_minima As \"Scorta Minima\", "
                          "ls.quantita AS \"Quantità\", "
                          "ls.prezzo_fattura::money As \"Prezzo Fattura\", "
                          "format('%s%%', ls.sconto_fornitore) As \"Sconto Fornitore\", "
                          "ls.prezzo_acquisto::money As \"Prezzo Acquisto\", "
                          "format('%s%%', ls.ricarico) As \"Ricarico\", "
                          "ls.iva::money As \"Iva\", "
                          "ls.prezzo_finito::money As \"Prezzo Finito\", "
                          "ls.prezzo_vendita::money As \"Prezzo Vendità\", "
                          "ls.prezzo_vendita_b::money As \"Prezzo Vendità B\", "
                          "ls.fattura As \"Nr.Fattura\", "
                          "ls.data_arrivo As \"Data Arrivo\", "
                          "mg.note As \"Note\" "
                          "FROM magazzino AS mg, anagrafica AS an, listino_storico AS ls "
                          "WHERE mg.id_fornitore=an.id AND mg.id=ls.id_articolo "
                          "AND rag_sociale='%1' AND ls.fattura ILIKE '%%2%' "
                          "ORDER BY mg.descr, mg.id, ls.fattura, ls.data_arrivo DESC");

    //Filtro fornitore.
    const QString FILTER_FORNITORE = "AND an.rag_sociale='%1' ORDER BY mg.descr";

    //Filtro fornitore e data corrente.
    const QString FILTER_CURRENT_DATE =
            "AND an.rag_sociale='%1' AND mg.data_arrivo=current_date "
            "ORDER BY mg.descr";

    //Select utilizzata per la stampa dell'inventario
    const QString SELECT_INVENTARIO = "SELECT * FROM vw_inventario WHERE \"Quantità\"!=0";

    //Select che ritorna il totale dell'inventario, usato insieme alla query SELECT_INVENTARIO
    const QString SQL_INVENTARIO_TOT =
            QString::fromUtf8("SELECT sum(\"SubTotale\") AS \"Totale\" "
                              "FROM vw_inventario");

    //SETTINGS
    const QString listinoCols = "Listino.cols";
    const QString ordineCols = "Ordine.cols";
    const QString listinoFont = "Listino.font";
    const QString ordineFont = "ordine.font";
}

namespace align {
    const QString left = "Sinistra";
    const QString right = "Destra";
    const QString center = "Centrale";
}

#endif // REPORT_CONST_H
