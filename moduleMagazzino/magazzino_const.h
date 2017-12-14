#ifndef MAGAZZINO_CONST_H
#define MAGAZZINO_CONST_H

#include <QString>
#include <QRect>
#include <QMap>
#include <QSqlQueryModel>

namespace sql {
    //Select utilizzata in MagazzinoWindow, elenca tutti gli articoli in magazzino
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

    //Select usata nei combobox per la selezione del fornitore.
    const QString SELECT_FORNITORE = "SELECT id, rag_sociale FROM anagrafica "
                                     "WHERE fornitore=true ORDER BY rag_sociale";
}

namespace magazzino {

    const QString CSS_WARNING_STYLE = "background-color:yellow";

    //SETTINGS
    const QString DEFAULT_IVA = "default.civa";
    const QString ARTICOLO_COLORS = "MagazzinoWindow.cols.colors.articolo";
    const QString ARTICOLO_STATUS = "MagazzinoWindow.cols.status.articolo";

    const QString STORICO_COLORS = "MagazzinoWindow.cols.colors.storico";
    const QString STORICO_STATUS = "MagazzinoWindow.cols.status.storico";

    const QString SEARCH_DESCR = "MagazzinoWindow.search.descrizione";
    const QString SEARCH_COD_ART = "MagazzinoWindow.search.codarticolo";
    const QString SEARCH_COD_FRN = "MagazzinoWindow.search.codfornitore";
    const QString SEARCH_COD_EAN = "MagazzinoWindow.search.codean";




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

    //Queste sono le colonne dei model di selezione dei combobox,
    //solitamente sono piccole tabelle di due colonne id e descrizione.
    enum Columns {
        COL_TABLE_ID = 0,
        COL_TABLE_DESCRIZIONE = 1
                 };
}
#endif // MAGAZZINO_CONST_H
