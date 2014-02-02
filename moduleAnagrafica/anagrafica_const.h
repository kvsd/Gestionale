#ifndef ANAGRAFICA_CONST_H
#define ANAGRAFICA_CONST_H

#include <QString>

namespace anagrafica {
    const QString SELECT_ALL = "SELECT * FROM vw_anagrafica WHERE \"Id\">0";
    const QString SELECT_CLNT = "SELECT * FROM vw_anagrafica_clienti WHERE \"Id\">0";
    const QString SELECT_FORN = "SELECT * FROM vw_anagrafica_fornitori WHERE \"Id\">0";
    const QString SELECT_FROM_ID = "SELECT * FROM anagrafica WHERE id=:id";

    const QString INSERT_QUERY = "INSERT INTO anagrafica(fornitore, cliente, rag_sociale, id_tipo_ditta, nome, cognome, indirizzo, id_citta, id_provincia, id_cap, id_stato, cod_fisc, prt_iva, id_agente, tel, fax, cel, email, sito_web, banca, agenzia, conto, swift, iban, dest_merce, note) VALUES(:fornitore, :cliente, :rag_sociale, :id_tipo_ditta, :nome, :cognome, :indirizzo, :id_citta, :id_provincia, :id_cap, :id_stato, :cod_fisc, :prt_iva, :id_agente, :tel, :fax, :cel, :email, :sito_web, :banca, :agenzia, :conto, :swift, :iban, :dest_merce, :note)";
    const QString UPDATE_QUERY = "UPDATE anagrafica SET fornitore=:fornitore, cliente=:cliente, rag_sociale=:rag_sociale, id_tipo_ditta=:id_tipo_ditta, nome=:nome, cognome=:cognome, indirizzo=:indirizzo, id_citta=:id_citta, id_provincia=:id_provincia, id_cap=:id_cap, id_stato=:id_stato, cod_fisc=:cod_fisc, prt_iva=:prt_iva, id_agente=:id_agente, tel=:tel, fax=:fax, cel=:cel, email=:email, sito_web=:sito_web, banca=:banca, agenzia=:agenzia, conto=:conto, swift=:swift, iban=:iban, dest_merce=:dest_merce, note=:note WHERE id=:id";
    const QString DELETE_QUERY = "DELETE FROM anagrafica WHERE id = :id";

    const QString CSS_WARNING_STYLE = "background-color:yellow";

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
