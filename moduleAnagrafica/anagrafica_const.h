#ifndef ANAGRAFICA_CONST_H
#define ANAGRAFICA_CONST_H

#include <QString>
#include <QRect>

namespace anagrafica {

    //SETTINGS
    const QString SEARCH_RAGSOCL = "AnagraficaWindow.search.ragcociale";
    const QString SEARCH_COGNOME = "AnagraficaWindow.search.cognome";
    const QString SEARCH_CODFISC = "AnagraficaWindow.search.codfisc";
    const QString SEARCH_PIVA = "AnagraficaWindow.search.piva";
    const QString CSS_WARNING_STYLE = "background-color:yellow";
    const QString ANGRFC_STATUS ="AnagraficaColsStatus";
    const QString ANGRFC_COLORS = "AnagraficaColsColors";

    //SQL

    //Query utilizzata nella view di AnagraficaWindow, elenca tutti i fornitori e i clienti.
    const QString SELECT_ALL =
    "SELECT anagrafica.id AS \"Id\", "
           "anagrafica.rag_sociale AS \"Ragione sociale\", "
           "anagrafica.nome AS \"Nome\", "
           "anagrafica.cognome AS \"Cognome\", "
           "anagrafica.indirizzo AS \"Indirizzo\", "
           "anagrafica.cod_fisc AS \"Codice fiscale\", "
           "anagrafica.prt_iva AS \"Partita Iva\", "
           "anagrafica.tel AS \"Telefono\", "
           "anagrafica.fax AS \"Fax\", "
           "anagrafica.cel AS \"Cellulare\", "
           "anagrafica.email AS \"Email\", "
           "anagrafica.sito_web AS \"Sito web\", "
           "anagrafica.banca AS \"Banca\", "
           "anagrafica.agenzia AS \"Agenzia\", "
           "anagrafica.conto AS \"Conto\", "
           "anagrafica.swift AS \"Swift\", "
           "anagrafica.iban AS \"Iban\", "
           "anagrafica.dest_merce AS \"Destinazione merce\", "
           "anagrafica.note AS \"Note\" "
    "FROM anagrafica, agenti "
    "WHERE anagrafica.id > 0 AND id_agente=agenti.id ";

    const QString FILTER_CLIENTE = "anagrafica.cliente=TRUE ";
    const QString FILTER_FORNITORE = "anagrafica.fornitore=TRUE ";
    const QString ORDER_CLAUSE = " ORDER BY anagrafica.rag_sociale";

    const QString SELECT_FROM_ID = "SELECT * FROM anagrafica WHERE id=:id";

    //Insert utilizzata in AnagraficaAddDialog per aggiungere un nuovo cliente/fornitore
    const QString INSERT_QUERY = "INSERT INTO anagrafica(fornitore, cliente, "
                                                        "rag_sociale, id_tipo_ditta, "
                                                        "nome, cognome, indirizzo, "
                                                        "id_citta, id_provincia, "
                                                        "id_cap, id_stato, cod_fisc, "
                                                        "prt_iva, id_agente, tel, "
                                                        "fax, cel, email, "
                                                        "sito_web, banca, agenzia, "
                                                        "conto, swift, iban, "
                                                        "dest_merce, note) "
                                 "VALUES(:fornitore, :cliente, :rag_sociale, :id_tipo_ditta, "
                                        ":nome, :cognome, :indirizzo, :id_citta, :id_provincia, "
                                        ":id_cap, :id_stato, :cod_fisc, :prt_iva, :id_agente, "
                                        ":tel, :fax, :cel, :email, :sito_web, :banca, :agenzia, "
                                        ":conto, :swift, :iban, :dest_merce, :note)";

    //Update utilizzata in AnagraficaAddDialog per aggiornare un cliente/fornitore
    const QString UPDATE_QUERY =
            "UPDATE anagrafica SET fornitore=:fornitore, cliente=:cliente, "
                                  "rag_sociale=:rag_sociale, "
                                  "id_tipo_ditta=:id_tipo_ditta, "
                                  "nome=:nome, cognome=:cognome, "
                                  "indirizzo=:indirizzo, id_citta=:id_citta, "
                                  "id_provincia=:id_provincia, id_cap=:id_cap, "
                                  "id_stato=:id_stato, cod_fisc=:cod_fisc, "
                                  "prt_iva=:prt_iva, id_agente=:id_agente, "
                                  "tel=:tel, fax=:fax, cel=:cel, email=:email, "
                                  "sito_web=:sito_web, banca=:banca, "
                                  "agenzia=:agenzia, conto=:conto, swift=:swift, "
                                  "iban=:iban, dest_merce=:dest_merce, note=:note "
            "WHERE id=:id";

    //Delete utilizzata in AnagraficaWindow per cancellare un cliente/fornitore
    const QString DELETE_QUERY = "DELETE FROM anagrafica WHERE id = :id";


    //COLS
    enum columns {COL_TABLE_ID = 0,
                  COL_TABLE_DESCRIZIONE = 1,
                  COL_TABLE_COGNOME = 2 //tabella agenti
                 };
}

#endif // ANAGRAFICA_CONST_H
