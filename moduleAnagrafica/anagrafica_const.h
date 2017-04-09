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
    //const QString ANGRFC_HEADER = "AnagraficaWindow.header";
    //const QString GEOMETRY = "AnagraficaWindow.size";
    //const QString SPLITTER_FILTRI_STATE = "AnagraficaWindow.splitter_filtri";
    //const QString SPLITTER_DOCS_STATE = "AnagraficaWindow.splitter_docs";

    //const QRect DEFAULT_GEOMETRY = QRect(0, 0, 700, 500);

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
           "agenti.cognome AS \"Agente\", "
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

    //PLACEHOLDERS SQL utilizzate nelle query insert/update/delete
    const QString PH_ID = ":id";
    const QString PH_FORNITORE = ":fornitore";
    const QString PH_CLIENTE = ":cliente";
    const QString PH_RAG_SOCIALE = ":rag_sociale";
    const QString PH_TIPO_DITTA = ":id_tipo_ditta";
    const QString PH_NOME = ":nome";
    const QString PH_COGNOME = ":cognome";
    const QString PH_INDIRIZZO = ":indirizzo";
    const QString PH_CITTA = ":id_citta";
    const QString PH_PROVINCIA = ":id_provincia";
    const QString PH_CAP = ":id_cap";
    const QString PH_STATO = ":id_stato";
    const QString PH_COD_FISCALE = ":cod_fisc";
    const QString PH_PRT_IVA = ":prt_iva";
    const QString PH_AGENTE = ":id_agente";
    const QString PH_TEL = ":tel";
    const QString PH_FAX = ":fax";
    const QString PH_CEL = ":cel";
    const QString PH_EMAIL = ":email";
    const QString PH_SITO_WEB = ":sito_web";
    const QString PH_BANCA = ":banca";
    const QString PH_AGENZIA = ":agenzia";
    const QString PH_CONTO = ":conto";
    const QString PH_SWIFT = ":swift";
    const QString PH_IBAN = ":iban";
    const QString PH_DEST_MERCE = ":dest_merce";
    const QString PH_NOTE = ":note";

    //COLS
    enum columns {COL_TABLE_ID = 0,
                  COL_TABLE_DESCRIZIONE = 1,
                  COL_TABLE_COGNOME = 2 //tabella agenti
                 };

    //Nomi delle colonne della tabella anagrafica.
    const QString COL_ID = "id";
    const QString COL_FORNITORE = "fornitore";
    const QString COL_CLIENTE = "cliente";
    const QString COL_RAGIONE_SOCIALE = "rag_sociale";
    const QString COL_ID_TIPO_DITTA = "id_tipo_ditta";
    const QString COL_NOME = "nome";
    const QString COL_COGNOME = "cognome";
    const QString COL_INDIRIZZO = "indirizzo";
    const QString COL_ID_CITTA = "id_citta";
    const QString COL_ID_PROVINCIA = "id_provincia";
    const QString COL_ID_CAP = "id_cap";
    const QString COL_ID_STATO = "id_stato";
    const QString COL_CODICE_FISCALE = "cod_fisc";
    const QString COL_PARTITA_IVA = "prt_iva";
    const QString COL_ID_AGENTE = "id_agente";
    const QString COL_TELEFONO = "tel";
    const QString COL_FAX = "fax";
    const QString COL_CELLULARE = "cel";
    const QString COL_EMAIL = "email";
    const QString COL_SITO_WEB = "sito_web";
    const QString COL_BANCA = "banca";
    const QString COL_AGENZIA = "agenzia";
    const QString COL_CONTO = "conto";
    const QString COL_SWIFT = "swift";
    const QString COL_IBAN = "iban";
    const QString COL_DESTINAZIONE_MERCE = "dest_merce";
    const QString COL_NOTE = "note";
}

#endif // ANAGRAFICA_CONST_H
