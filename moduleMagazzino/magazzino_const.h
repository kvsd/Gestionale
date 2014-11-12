#ifndef MAGAZZINO_CONST_H
#define MAGAZZINO_CONST_H

#include <QString>
#include <QRect>
#include <QMap>

namespace magazzino {

    const int TAB_MAGAZZINO = 0;
    const int TAB_STORICO = 1;
    const QString CSV_VERSION = "CSV::1.0";
    const QRect DEFAULT_WINDOW_SIZE = QRect(0, 0, 700, 500);

    const int PRINT_TITLE_HEIGHT = 500;
    const int PRINT_COLS_HEIGHT = 300;
    const int PRINT_MARGINS = 50;

    //SETTINGS
    const QString DEFAULT_IVA = "default.civa";
    const QString ARTICOLO_COLORS = "MagazzinoWindow.cols.colors.articolo";
    const QString ARTICOLO_STATUS = "MagazzinoWindow.cols.status.articolo";
    const QString ARTICOLO_HEADER = "MagazzinoWindow.header.articolo";

    const QString STORICO_COLORS = "MagazzinoWindow.cols.colors.storico";
    const QString STORICO_STATUS = "MagazzinoWindow.cols.status.storico";
    const QString STORICO_HEADER = "MagazzinoWindow.header.storico";

    const QString WINDOW_SIZE = "MagazzinoWindow.size";
    const QString SPLITTER1_SIZE = "MagazzinoWindow.size.splitter1";
    const QString SPLITTER2_SIZE = "MagazzinoWindow.size.splitter2";

    const QString SEARCH_DESCR = "MagazzinoWindow.search.descrizione";
    const QString SEARCH_COD_ART = "MagazzinoWindow.search.codarticolo";
    const QString SEARCH_COD_FRN = "MagazzinoWindow.search.codfornitore";
    const QString SEARCH_COD_EAN = "MagazzinoWindow.search.codean";

    const QString LISTINO_COL1 = "Listino.col1";
    const QString LISTINO_COL2 = "Listino.col2";
    const QString LISTINO_COL3 = "Listino.col3";
    const QString LISTINO_COL4 = "Listino.col4";

    const QString ORDINE_COL1 = "Ordine.col1";
    const QString ORDINE_COL2 = "Ordine.col2";
    const QString ORDINE_COL3 = "Ordine.col3";
    const QString ORDINE_COL4 = "Ordine.col4";


    //SQL
    const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, \"Ragione sociale\" as descr FROM vw_anagrafica_fornitori";

    const QString SELECT_FORNITORE = "SELECT \"Id\", \"Ragione sociale\" from vw_anagrafica_fornitori ORDER BY \"Ragione sociale\"";

    const QString INSERT_STORICO = "INSERT INTO listino_storico (id_articolo, data_arrivo, quantita, prezzo_fattura, sconto_fornitore, prezzo_acquisto, ricarico, iva, prezzo_finito, prezzo_vendita, fattura) VALUES (:id_articolo, :data_arrivo, :quantita, :prezzo_fattura, :sconto_fornitore, :prezzo_acquisto, :ricarico, :iva, :prezzo_finito, :prezzo_vendita, :fattura)";
    const QString SELECT_STORICO = "SELECT * FROM vw_listino_storico WHERE \"Id Articolo\"='%1' ORDER BY \"Data\" DESC, \"Prezzo Acquisto\" DESC";
    const QString SELECT_CSV_STORICO = "SELECT * FROM listino_storico";

    const QString INSERT_ARTICOLO = "INSERT INTO magazzino (descr, id_fornitore, id_marca, modello, cod_articolo, cod_fornitore, cod_barre ,id_merce , cod_iva, id_unita_misura, scorta_minima, quantita, prezzo_fattura, sconto_fornitore, prezzo_acquisto, ricarico, iva, prezzo_finito, prezzo_vendita, fattura, data_arrivo, id_sede_magazzino, note) VALUES (:descr, :id_fornitore, :id_marca, :modello, :cod_articolo, :cod_fornitore, :cod_barre, :id_merce, :cod_iva, :id_unita_merce, :scorta_minima, :quantita, :prezzo_fattura, :sconto_fornitore, :prezzo_acquisto, :ricarico, :iva, :prezzo_finito, :prezzo_vendita, :fattura, :data_arrivo, :id_sede_magazzino, :note)";
    const QString DELETE_ARTICOLO = "DELETE FROM magazzino WHERE id = :id";
    const QString UPDATE_ARTICOLO = "UPDATE magazzino SET descr=:descr, id_fornitore=:id_fornitore, id_marca=:id_marca, modello=:modello, cod_articolo=:cod_articolo, cod_fornitore=:cod_fornitore, cod_barre=:cod_barre, id_merce=:id_merce, cod_iva=:cod_iva, id_unita_misura=:id_unita_merce, scorta_minima=:scorta_minima, quantita=:quantita, prezzo_fattura=:prezzo_fattura, sconto_fornitore=:sconto_fornitore, ricarico=:ricarico, prezzo_acquisto=:prezzo_acquisto, iva=:iva, prezzo_finito=:prezzo_finito, prezzo_vendita=:prezzo_vendita, fattura=:fattura, data_arrivo=:data_arrivo, id_sede_magazzino=:id_sede_magazzino, note=:note WHERE id=:id";
    const QString SELECT_FROM_ID = "SELECT * FROM magazzino WHERE id = :id";
    const QString INSERT_CSV_ARTICOLO = "INSERT INTO magazzino (id, descr, id_fornitore, id_marca, modello, cod_articolo, cod_fornitore, cod_barre ,id_merce ,cod_iva, id_unita_misura, scorta_minima, quantita, prezzo_fattura, sconto_fornitore, prezzo_acquisto, ricarico, iva, prezzo_finito, prezzo_vendita, fattura, data_arrivo, id_sede_magazzino, note) VALUES (:id, :descr, :id_fornitore, :id_marca, :modello, :cod_articolo, :cod_fornitore, :cod_barre, :id_merce, :cod_iva, :id_unita_merce, :scorta_minima, :quantita, :prezzo_fattura, :sconto_fornitore, :prezzo_acquisto, :ricarico, :iva, :prezzo_finito, :prezzo_vendita, :fattura, :data_arrivo, :id_sede_magazzino, :note)";
    const QString SELECT_CSV_MAGAZZINO = "SELECT * FROM magazzino";
    const QString SELECT_ARTICOLI_FROM_IVA = "SELECT * FROM magazzino WHERE cod_iva=:cod_iva";
    const QString UPDATE_ARTICOLI_FROM_IVA = "UPDATE magazzino SET cod_iva=:cod_iva, iva=:iva, prezzo_finito=:prezzo_finito, prezzo_vendita=:prezzo_vendita WHERE id=:id";

    const QString SELECT_ARTICOLI_ALL = "SELECT * FROM vw_magazzino";
    const QString SELECT_ARTICOLI_FROM_FORN = "SELECT * FROM vw_magazzino WHERE \"Fornitore\" = '%1'";
    const QString SELECT_INVENTARIO = QString::fromUtf8("SELECT \"Quantità\", \"Descrizione\", \"Prezzo Acquisto\", \"Quantità\"*\"Prezzo Acquisto\" As \"SubTotale\" FROM vw_magazzino WHERE \"Quantità\"!=0 ORDER BY \"Descrizione\" "); 
    const QString SQL_INVENTARIO_TOT = QString::fromUtf8("SELECT sum(\"Prezzo Acquisto\"*\"Quantità\") AS \"Totale\" FROM vw_magazzino WHERE \"Quantità\"!=0");
    const QString SELECT_ORDINE = QString::fromUtf8("SELECT * FROM vw_magazzino WHERE \"Quantità\" < \"Scorta Minima\" AND \"Fornitore\" = '%1'");

    enum Documenti {
        FATTURA,
        INVENTARIO,
        ORDINE,
        LISTINO
    };

    enum Columns {COL_MG_ID = 0,            // Id
                  COL_MG_DESCR = 1,         // Descrizione
                  COL_MG_ID_FORN = 2,       // Fornitore
                  COL_MG_ID_MARCA = 3,      // Marca
                  COL_MG_MODELLO = 4,       // Modello
                  COL_MG_COD_ART = 5,       // Cod.Articolo
                  COL_MG_COD_FOR = 6,       // Cod.Fornitore
                  COL_MG_COD_EAN = 7,       // Cod.EAN
                  COL_MG_ID_MERCE = 8,      // Cat.Merce
                  COL_MG_COD_IVA = 9,       // Cod.IVA
                  COL_MG_ID_UM = 10,        // UM
                  COL_MG_SCORTA = 11,       // Scorta Minima
                  COL_MG_QT = 12,           // Quantità
                  COL_MG_PRZ_FAT = 13,      // Prezzo Fattura
                  COL_MG_SCONTO = 14,       // Sconto
                  COL_MG_PRZ_ACQ = 15,      // Prezzo Acquisto
                  COL_MG_RICARICO = 16,     // Ricarico
                  COL_MG_IVA = 17,          // Iva
                  COL_MG_PRZ_FIN = 18,      // Prezzo Finito
                  COL_MG_PRZ_VEN = 19,      // Prezzo Vendità
                  COL_MG_FATTURA = 20,      // Nr.Fattura
                  COL_MG_DATA = 21,         // Data Arrivo
                  COL_MG_ID_SEDE = 22,      // Sede Magazzino
                  COL_MG_NOTE = 23,         // Note

                  COL_ST_ID_ARTICOLO = 0,   // Id Articolo
                  COL_ST_DATA = 1,          // Data
                  COL_ST_QT = 2,            // Quantita
                  COL_ST_PRZ_FAT = 3,       // Prezzo Fattura
                  COL_ST_SCONTO = 4,        // Sconto
                  COL_ST_PRZ_ACQ = 5,       // Prezzo Acquisto
                  COL_ST_RICARICO = 6,      // Ricarico
                  COL_ST_IVA = 7,           // IVA
                  COL_ST_PRZ_FIN = 8,       // Prezzo Finito
                  COL_ST_PRZ_VEN = 9,       // Prezzo Vendità
                  COL_ST_FATTURA = 10       // FATTURA
                 };

    QMap<int,QString> prepareMapsNameColsArticolo();
    QMap<int,QString> prepareMapsNameColsStorico();

    //PH SQL PlaceHolder
    const QString PH_ID      = ":id";
    const QString PH_DESCR   = ":descr";
    const QString PH_ID_FORN = ":id_fornitore";
    const QString PH_ID_MARC = ":id_marca";
    const QString PH_MODELLO = ":modello";
    const QString PH_COD_ART = ":cod_articolo";
    const QString PH_COD_FRN = ":cod_fornitore";
    const QString PH_COD_EAN = ":cod_barre";
    const QString PH_ID_MERC = ":id_merce";
    const QString PH_COD_IVA = ":cod_iva";
    const QString PH_ID_UM   = ":id_unita_merce";
    const QString PH_SCORTA  = ":scorta_minima";
    const QString PH_QUANTIT = ":quantita";
    const QString PH_PRZ_FAT = ":prezzo_fattura";
    const QString PH_SCONTO  = ":sconto_fornitore";
    const QString PH_PRZ_ACQ = ":prezzo_acquisto";
    const QString PH_RICARIC = ":ricarico";
    const QString PH_IVA     = ":iva";
    const QString PH_PRZ_FIN = ":prezzo_finito";
    const QString PH_PRZ_VEN = ":prezzo_vendita";
    const QString PH_FATTURA = ":fattura";
    const QString PH_DATA    = ":data_arrivo";
    const QString PH_ID_SEDE = ":id_sede_magazzino";
    const QString PH_NOTE    = ":note";
    const QString PH_ID_ART  = ":id_articolo";

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
    const QString CMP_SCONTO  = "Sconto";
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
#endif // MAGAZZINO_CONST_H
