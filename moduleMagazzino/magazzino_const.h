#ifndef MAGAZZINO_CONST_H
#define MAGAZZINO_CONST_H

#include <QString>
#include <QRect>
#include <QMap>
#include <QSqlQueryModel>

namespace magazzino {

    const QRect DEFAULT_GEOMETRY = QRect(0, 0, 700, 500);

    const QString CSS_WARNING_STYLE = "background-color:yellow";

    //SETTINGS
    const QString DEFAULT_IVA = "default.civa";
    const QString ARTICOLO_COLORS = "MagazzinoWindow.cols.colors.articolo";
    const QString ARTICOLO_STATUS = "MagazzinoWindow.cols.status.articolo";
    const QString ARTICOLO_HEADER = "MagazzinoWindow.header.articolo";

    const QString STORICO_COLORS = "MagazzinoWindow.cols.colors.storico";
    const QString STORICO_STATUS = "MagazzinoWindow.cols.status.storico";
    const QString STORICO_HEADER = "MagazzinoWindow.header.storico";

    const QString GEOMETRY = "MagazzinoWindow.size";
    const QString SPLITTER1_SIZE = "MagazzinoWindow.size.splitter1";
    const QString SPLITTER2_SIZE = "MagazzinoWindow.size.splitter2";

    const QString SEARCH_DESCR = "MagazzinoWindow.search.descrizione";
    const QString SEARCH_COD_ART = "MagazzinoWindow.search.codarticolo";
    const QString SEARCH_COD_FRN = "MagazzinoWindow.search.codfornitore";
    const QString SEARCH_COD_EAN = "MagazzinoWindow.search.codean";


    //SQL
    //Select usata nel combobox in MagazzinoWindow per il filtro fornitore.
    const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, "
                                                   "\"Ragione sociale\" as descr "
                                            "FROM vw_anagrafica_fornitori";

    //Select usate in ArticoloDialog per il combobox del fornitore
    const QString SELECT_FORNITORE = "SELECT \"Id\", \"Ragione sociale\" "
                                     "FROM vw_anagrafica_fornitori "
                                     "ORDER BY \"Ragione sociale\"";

    //Insert utilizzata per aggiungere un record in listino_storico
    //Viene utilizzata in ArticoloDialog, MagazzinoWindows(cvs) e CodIvaUpdateDialog
    const QString INSERT_STORICO =
            "INSERT INTO listino_storico (id_articolo, data_arrivo, quantita, "
                                         "prezzo_fattura, sconto_fornitore, "
                                         "prezzo_acquisto, ricarico, iva, "
                                         "prezzo_finito, prezzo_vendita, fattura) "
            "VALUES (:id_articolo, :data_arrivo, :quantita, :prezzo_fattura, "
                    ":sconto_fornitore, :prezzo_acquisto, :ricarico, :iva, "
                    ":prezzo_finito, :prezzo_vendita, :fattura)";

    //Update utilizzata per aggiornare un record in listino_storico
    //Viene utilizzata in ArticoloDialog al posto della insert se
    //viene trovata una coppia id_articolo, data_arrivo in listino_storico
    const QString UPDATE_STORICO =
            "UPDATE listino_storico SET quantita=:quantita, "
                                        "prezzo_fattura=:prezzo_fattura, "
                                        "sconto_fornitore=:sconto_fornitore, "
                                        "prezzo_acquisto=:prezzo_acquisto, "
                                        "ricarico=:ricarico, "
                                        "iva=:iva, "
                                        "prezzo_finito=:prezzo_finito, "
                                        "prezzo_vendita=:prezzo_vendita, "
                                        "fattura=:fattura "
            "WHERE id_articolo=:id_articolo AND data_arrivo=:data_arrivo";

    //Check utilizzata per cercare se all'interno della tabella listino_storico
    //sono presenti la coppia id_articolo,data_arrivo.
    const QString CHECK_STORICO =
            "SELECT * FROM listino_storico WHERE id_articolo=:id_articolo AND "
                                                 "data_arrivo=:data_arrivo";

    //Select utilizzata in MagazzinoWindow per visualizzare lo storico
    //del'articolo selezionato
    const QString SELECT_STORICO = "SELECT * FROM vw_listino_storico "
                                   "WHERE \"Id Articolo\"='%1' "
                                   "ORDER BY \"Data\" DESC, "
                                            "\"Prezzo Acquisto\" DESC";

    //Insert utilizzata in ArticoloDialog per l'inserimento di nuovi articoli
    const QString INSERT_ARTICOLO =
            "INSERT INTO magazzino (descr, id_fornitore, id_marca, modello, "
                                   "cod_articolo, cod_fornitore, cod_barre ,"
                                   "id_merce, cod_iva, id_unita_misura, "
                                   "scorta_minima, quantita, prezzo_fattura, "
                                   "sconto_fornitore, prezzo_acquisto, ricarico, "
                                   "iva, prezzo_finito, prezzo_vendita, fattura, "
                                   "data_arrivo, id_sede_magazzino, note) "
            "VALUES (:descr, :id_fornitore, :id_marca, :modello, :cod_articolo, "
                    ":cod_fornitore, :cod_barre, :id_merce, :cod_iva, :id_unita_merce, "
                    ":scorta_minima, :quantita, :prezzo_fattura, :sconto_fornitore, "
                    ":prezzo_acquisto, :ricarico, :iva, :prezzo_finito, :prezzo_vendita, "
                    ":fattura, :data_arrivo, :id_sede_magazzino, :note)";

    //Delete usata in MagazzinoWindow per eliminare l'articolo selezionato
    const QString DELETE_ARTICOLO = "DELETE FROM magazzino WHERE id = :id";

    //Update usata in ArticoloDialog per aggiornare l'articolo selezionato
    const QString UPDATE_ARTICOLO =
            "UPDATE magazzino SET descr=:descr, "
                                 "id_fornitore=:id_fornitore, "
                                 "id_marca=:id_marca, modello=:modello, "
                                 "cod_articolo=:cod_articolo, "
                                 "cod_fornitore=:cod_fornitore, "
                                 "cod_barre=:cod_barre, "
                                 "id_merce=:id_merce, "
                                 "cod_iva=:cod_iva, "
                                 "id_unita_misura=:id_unita_merce, "
                                 "scorta_minima=:scorta_minima, "
                                 "quantita=:quantita, "
                                 "prezzo_fattura=:prezzo_fattura, "
                                 "sconto_fornitore=:sconto_fornitore, "
                                 "ricarico=:ricarico, "
                                 "prezzo_acquisto=:prezzo_acquisto, "
                                 "iva=:iva, "
                                 "prezzo_finito=:prezzo_finito, "
                                 "prezzo_vendita=:prezzo_vendita, "
                                 "fattura=:fattura, "
                                 "data_arrivo=:data_arrivo, "
                                 "id_sede_magazzino=:id_sede_magazzino, "
                                 "note=:note "
            "WHERE id=:id";

    //Select usata in ArticoloDialog per caricare tutti i dati per la modifica
    //di un articolo
    const QString SELECT_FROM_ID = "SELECT * FROM magazzino WHERE id = :id";

    //Select utilizzata in CodIvaUpdateDialog
    const QString SELECT_ARTICOLI_FROM_IVA = "SELECT * FROM magazzino WHERE cod_iva=:cod_iva";

    //Update utilizzata in CodIvaUpdateDialog
    const QString UPDATE_ARTICOLI_FROM_IVA =
            "UPDATE magazzino SET cod_iva=:cod_iva, "
                                 "iva=:iva, "
                                 "prezzo_finito=:prezzo_finito, "
                                 "prezzo_vendita=:prezzo_vendita "
            "WHERE id=:id";

    //Select utilizzata in MagazzinoWindow, elenca tutti gli articoli in magazzino
    //sostituisce vw_magazzino
    const QString SELECT_ARTICOLI_ALL =
            QString::fromUtf8("SELECT mg.id As \"Id\", "
                                     "mg.descr As \"Descrizione\", "
                                     "an.rag_sociale AS \"Fornitore\", "
                                     "mg.modello As \"Modello\", "
                                     "mg.cod_articolo AS \"Cod.Articolo\", "
                                     "mg.cod_fornitore AS \"Cod.Fornitore\", "
                                     "mg.cod_barre AS \"Cod.EAN\", "
                                     "format('%s%%', mg.cod_iva) AS \"Cod.IVA\", "
                                     "mg.scorta_minima As \"Scorta Minima\", "
                                     "mg.quantita AS \"Quantità\", "
                                     "mg.prezzo_fattura::money As \"Prezzo Fattura\", "
                                     "format('%s%%', mg.sconto_fornitore) As \"Sconto Fornitore\", "
                                     "mg.prezzo_acquisto::money As \"Prezzo Acquisto\", "
                                     "format('%s%%', mg.ricarico) As \"Ricarico\", "
                                     "mg.iva::money As \"Iva\", "
                                     "mg.prezzo_finito::money As \"Prezzo Finito\", "
                                     "mg.prezzo_vendita::money As \"Prezzo Vendità\", "
                                     "mg.fattura As \"Nr.Fattura\", "
                                     "mg.data_arrivo As \"Data Arrivo\", "
                                     "mg.note As \"Note\" "
                              "FROM magazzino AS mg, anagrafica AS an "
                              "WHERE mg.id_fornitore=an.id ");


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
}
#endif // MAGAZZINO_CONST_H
