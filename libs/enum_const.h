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
