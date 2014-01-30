#ifndef ENUM_CONST_H
#define ENUM_CONST_H

namespace agenti {
    enum columns {COL_ID,
                  COL_NOME,
                  COL_COGNOME,
                  COL_TEL,
                  COL_CEL,
                  COL_EMAIL};
}

namespace anagrafica {
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

namespace azienda {
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
                  COL_CCIAA};
}


#endif // ENUM_CONST_H
