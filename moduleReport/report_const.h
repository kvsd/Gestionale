#ifndef REPORT_CONST_H
#define REPORT_CONST_H

#include <QString>
#include <QRect>
#include <QMap>

namespace report {

    const QRect DEFAULT_GEOMETRY = QRect(0, 0, 700, 500);

    const int PRINT_TITLE_HEIGHT = 500;
    const int PRINT_COLS_HEIGHT = 300;
    const int PRINT_MARGINS = 50;


    //SETTINGS
    const QString GEOMETRY = "MagazzinoWindow.size";

    const QString LISTINO_COL1 = "Listino.col1";
    const QString LISTINO_COL2 = "Listino.col2";
    const QString LISTINO_COL3 = "Listino.col3";
    const QString LISTINO_COL4 = "Listino.col4";

    const QString ORDINE_COL1 = "Ordine.col1";
    const QString ORDINE_COL2 = "Ordine.col2";
    const QString ORDINE_COL3 = "Ordine.col3";
    const QString ORDINE_COL4 = "Ordine.col4";


    //Select usata nel combobox in MagazzinoWindow per il filtro fornitore.
    const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, "
                                                   "\"Ragione sociale\" as descr "
                                            "FROM vw_anagrafica_fornitori";

    //Select utilizzata per la stampa dei listini
    //const QString SELECT_ARTICOLI_FROM_FORN = "SELECT * FROM vw_magazzino WHERE \"Fornitore\" = '%1'";

    //Select utilizzata per la stampa dell'inventario
    const QString SELECT_INVENTARIO = "SELECT * FROM vw_inventario";

    //Select che ritorna il totale dell'inventario, usato insieme alla query SELECT_INVENTARIO
    const QString SQL_INVENTARIO_TOT =
            QString::fromUtf8("SELECT sum(\"Prezzo Acquisto\"*\"Quantità\") AS \"Totale\" "
                              "FROM vw_magazzino WHERE \"Quantità\"!=0");

    //Select utilizzata per la stampa degli ordini
    const QString SELECT_ORDINE =
            QString::fromUtf8("SELECT * FROM vw_magazzino "
                              "WHERE \"Quantità\" <= \"Scorta Minima\" "
                              "AND \"Fornitore\" = '%1'");

    enum Documenti {
        FATTURA,
        INVENTARIO,
        ORDINE,
        LISTINO
    };

}
#endif // REPORT_CONST_H
