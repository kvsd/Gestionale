#ifndef GESTIONALE_CONST_H
#define GESTIONALE_CONST_H

#include <QString>

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

namespace table {
    const QString AGENTI = "agenti";
    const QString AGENZIA = "agenzia";
    const QString ANAGRAFICA = "anagrafica";
    const QString ASPETTO_BENI = "aspetto_beni";
    const QString AZIENDA = "azienda";
    const QString BANCA = "banca";
    const QString CAP = "cap";
    const QString CASUALE_TRASPORTO = "casuale_trasporto";
    const QString CATEGORIA_MERCE = "cat_merce";
    const QString CITTA = "citta";
    const QString CODICE_IVA = "cod_iva";
    const QString LISTINO_STORICO = "listino_storico";
    const QString MAGAZZINO = "magazzino";
    const QString MARCA = "marca";
    const QString PROVINCIA = "provincia";
    const QString SEDE_MAGAZZINO = "sede_magazzino";
    const QString STATO = "stato";
    const QString TIPO_DITTA = "tipo_ditta";
    const QString TIPO_PAGAMENTO = "tipo_pagamento";
    const QString UNITA_MISURA = "unita_misura";
    const QString USER_DB = "user_db";
    const QString VETTORE = "vettore";
}

#endif // GESTIONALE_CONST_H
