#ifndef ANAGRAFICA_CONST_H
#define ANAGRAFICA_CONST_H

#include <QString>
#include <QRect>

namespace anagrafica {

    //SETTINGS
    const QString SEARCH_DENOM = "AnagraficaWindow.search.denom";
    const QString SEARCH_COGNOME = "AnagraficaWindow.search.cognome";
    const QString SEARCH_CODFISC = "AnagraficaWindow.search.codfisc";
    const QString SEARCH_PIVA = "AnagraficaWindow.search.piva";
    const QString ANGRFC_STATUS ="AnagraficaColsStatus";
    const QString ANGRFC_COLORS = "AnagraficaColsColors";

    //SQL

    //Query utilizzata nella view di AnagraficaWindow, elenca tutti i fornitori e i clienti.
    const QString SELECT_ALL =
    "SELECT anagrafica.id AS \"Id\", "
           "anagrafica.denominazione AS \"Denominazione\", "
           "anagrafica.nome AS \"Nome\", "
           "anagrafica.cognome AS \"Cognome\", "
           "anagrafica.cod_sdi AS \"COD.SDI\", "
           "anagrafica.pec AS \"PEC\", "
           "anagrafica.cod_fisc AS \"Codice fiscale\", "
           "anagrafica.prt_iva AS \"Partita Iva\", "
           "anagrafica.indirizzo AS \"Indirizzo\", "
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

    const QString ORDER_CLAUSE = " ORDER BY anagrafica.denominazione";

    const QString SELECT_FROM_ID = "SELECT * FROM anagrafica WHERE id=:id";

    //Insert utilizzata in AnagraficaAddDialog per aggiungere un nuovo cliente/fornitore
    const QString INSERT_QUERY = "INSERT INTO anagrafica(azienda, cliente, fornitore, pa, "
                                                        "denominazione, nome, "
                                                        "cognome, id_trasmissione, "
                                                        "cod_sdi, pec, "
                                                        "indirizzo, "
                                                        "id_citta, id_provincia, "
                                                        "id_cap, id_stato, cod_fisc, "
                                                        "prt_iva, id_agente, tel, "
                                                        "fax, cel, email, "
                                                        "sito_web, banca, agenzia, "
                                                        "conto, swift, iban, "
                                                        "dest_merce, note) "
                                 "VALUES(:azienda, :cliente, :fornitore, :pa, :denominazione, "
                                        ":nome, :cognome, :id_trasmissione, :cod_sdi, :pec, :indirizzo, "
                                        ":id_citta, :id_provincia, :id_cap, :id_stato, :cod_fisc, "
                                        ":prt_iva, :id_agente, :tel, :fax, :cel, :email, :sito_web, "
                                        ":banca, :agenzia, :conto, :swift, :iban, :dest_merce, :note) "
                                 "RETURNING id";

    //Update utilizzata in AnagraficaAddDialog per aggiornare un cliente/fornitore
    const QString UPDATE_QUERY =
            "UPDATE anagrafica SET azienda=:azienda, cliente=:cliente, "
                                  "fornitore=:fornitore, pa=:pa, "
                                  "denominazione=:denominazione, "
                                  "nome=:nome, cognome=:cognome, "
                                  "id_trasmissione = :id_trasmissione, "
                                  "cod_sdi=:cod_sdi, pec=:pec, "
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

    enum class cols {id=0, descr=1, cognome=2, denominazione=5};
}

#endif // ANAGRAFICA_CONST_H
