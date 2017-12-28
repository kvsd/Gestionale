#ifndef REPORT_CONST_H
#define REPORT_CONST_H

#include "magazzino_const.h"
#include <QString>

namespace sql {
    //Filtro fornitore.
    const QString FILTER_FORNITORE = "AND an.rag_sociale=:rag_sociale ORDER BY mg.descr";

    //Filtro fornitore e data corrente.
    const QString FILTER_CURRENT_DATE =
            "AND an.rag_sociale=:rag_sociale AND mg.data_arrivo=current_date "
            "ORDER BY mg.descr";

    //Filtro fornitore e numero fattura.
    const QString FILTER_FATTURA = " AND rag_sociale=:rag_sociale"
            " AND fattura ILIKE :fattura ORDER BY descr";

    //Select utilizzata per la stampa dell'inventario
    const QString SELECT_INVENTARIO = "SELECT * FROM vw_inventario WHERE \"Quantità\"!=0";

    //Select che ritorna il totale dell'inventario, usato insieme alla query SELECT_INVENTARIO
    const QString SQL_INVENTARIO_TOT =
            QString::fromUtf8("SELECT sum(\"SubTotale\") AS \"Totale\" "
                              "FROM vw_inventario");
}

namespace settings {
    //SETTINGS
    const QString listinoCols = "Listino.cols";
    const QString ordineCols = "Ordine.cols";
    const QString listinoFont = "Listino.font";
    const QString ordineFont = "ordine.font";
}

namespace CPD {
    //Colonne ConfigPrintDialog.TableWidget
    enum col{
        DESCR = 0,
        STRETCH = 1,
        VIEW = 2,
        ALIGN = 3
    };
}

namespace align {
    const QString left = "Sinistra";
    const QString right = "Destra";
    const QString center = "Centrale";
}

#endif // REPORT_CONST_H
