#ifndef AZIENDA_CONST_H
#define AZIENDA_CONST_H

#include <QString>

namespace azienda {

    const int WIDTH = 300;
    const int HEIGHT = 200;
    const QString CSS_WARNING_STYLE = "background-color:yellow";

    const QString SELECT_QUERY = "SELECT * FROM azienda WHERE id=0";
    const QString UPDATE_QUERY = "UPDATE azienda SET rag_sociale=:rag_sociale, nome=:nome, cognome=:cognome, indirizzo=:indirizzo, id_citta=:id_citta, id_provincia=:id_provincia, id_cap=:id_cap, id_stato=:id_stato, tel=:tel, fax=:fax, email=:email, prt_iva=:prt_iva, cod_fisc=:cod_fisc, iscr_trib=:iscr_trib, cciaa=:cciaa, reg_imprese=:reg_imprese, logo=:logo WHERE id=0";

    enum columns {COL_ID,
                  COL_RAG_SOC, COL_DESCR=1,
                  COL_NOME,
                  COL_COGNOME,
                  COL_INDIRIZZO,
                  COL_CITTA,
                  COL_PROVINCIA,
                  COL_CAP,
                  COL_STATO,
                  COL_TEL,
                  COL_FAX,
                  COL_EMAIL,
                  COL_PRT_IVA,
                  COL_COD_FISC,
                  COL_TRIB,
                  COL_CCIAA,
                  COL_REG_IMPRESE,
                  COL_LOGO};

    const QString PH_ID = ":id";
    const QString PH_RAG_SOCIALE = ":rag_sociale";
    const QString PH_NOME = ":nome";
    const QString PH_COGNOME = ":cognome";
    const QString PH_INDIRIZZO = ":indirizzo";
    const QString PH_CITTA = ":id_citta";
    const QString PH_PROVINCIA = ":id_provincia";
    const QString PH_CAP = ":id_cap";
    const QString PH_STATO = ":id_stato";
    const QString PH_TEL = ":tel";
    const QString PH_FAX = ":fax";
    const QString PH_EMAIL = ":email";
    const QString PH_PRT_IVA = ":prt_iva";
    const QString PH_COD_FISC = ":cod_fisc";
    const QString PH_ISCR_TRIB = ":iscr_trib";
    const QString PH_CCIAA = ":cciaa";
    const QString PH_REG_IMPRESE = ":reg_imprese";
    const QString PH_LOGO = ":logo";
}
#endif // AZIENDA_CONST_H
