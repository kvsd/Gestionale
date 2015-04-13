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
    const QString ANGRFC_HEADER = "AnagraficaWindow.header";
    const QString ANGRFC_SIZE = "AnagraficaWindow.size";
    const QString ANGRFC_SPLITTER_FLT = "AnagraficaWindow.splitter_filtri";

    const QRect DEFAULT_SIZE = QRect(0, 0, 700, 500);

    //SQL
    const QString SELECT_ALL = "SELECT * FROM vw_anagrafica WHERE \"Id\">0";
    const QString SELECT_CLNT = "SELECT * FROM vw_anagrafica_clienti WHERE \"Id\">0";
    const QString SELECT_FORN = "SELECT * FROM vw_anagrafica_fornitori WHERE \"Id\">0";
    const QString SELECT_FROM_ID = "SELECT * FROM anagrafica WHERE id=:id";

    const QString INSERT_QUERY = "INSERT INTO anagrafica(fornitore, cliente, rag_sociale, id_tipo_ditta, nome, cognome, indirizzo, id_citta, id_provincia, id_cap, id_stato, cod_fisc, prt_iva, id_agente, tel, fax, cel, email, sito_web, banca, agenzia, conto, swift, iban, dest_merce, note) VALUES(:fornitore, :cliente, :rag_sociale, :id_tipo_ditta, :nome, :cognome, :indirizzo, :id_citta, :id_provincia, :id_cap, :id_stato, :cod_fisc, :prt_iva, :id_agente, :tel, :fax, :cel, :email, :sito_web, :banca, :agenzia, :conto, :swift, :iban, :dest_merce, :note)";
    const QString UPDATE_QUERY = "UPDATE anagrafica SET fornitore=:fornitore, cliente=:cliente, rag_sociale=:rag_sociale, id_tipo_ditta=:id_tipo_ditta, nome=:nome, cognome=:cognome, indirizzo=:indirizzo, id_citta=:id_citta, id_provincia=:id_provincia, id_cap=:id_cap, id_stato=:id_stato, cod_fisc=:cod_fisc, prt_iva=:prt_iva, id_agente=:id_agente, tel=:tel, fax=:fax, cel=:cel, email=:email, sito_web=:sito_web, banca=:banca, agenzia=:agenzia, conto=:conto, swift=:swift, iban=:iban, dest_merce=:dest_merce, note=:note WHERE id=:id";
    const QString DELETE_QUERY = "DELETE FROM anagrafica WHERE id = :id";

    //PLACEHOLDERS SQL
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
    enum columns {COL_ID,
                  COL_FORNITORE, COL_MODEL_DESCR = 1,
                  COL_CLIENTE, COL_MODEL_COGNOME = 2,
                  COL_RAG_SOC,
                  COL_TIPO_DITTA,
                  COL_NOME,
                  COL_COGNOME,
                  COL_INDIRIZZO,
                  COL_CITTA,
                  COL_PROVINCIA,
                  COL_CAP,
                  COL_STATO,
                  COL_COD_FISC,
                  COL_PRT_IVA,
                  COL_AGENTE,
                  COL_TEL,
                  COL_FAX,
                  COL_CEL,
                  COL_EMAIL,
                  COL_WEB,
                  COL_BANCA,
                  COL_AGENZIA,
                  COL_CONTO,
                  COL_SWIFT,
                  COL_IBAN,
                  COL_MERCE,
                  COL_NOTE};
}

#endif // ANAGRAFICA_CONST_H
