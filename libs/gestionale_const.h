#ifndef GESTIONALE_CONST_H
#define GESTIONALE_CONST_H

#include <QString>

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

namespace ph {
    const QString AGENTE = ":id_agente";
    const QString AGENZIA = ":agenzia";
    const QString BANCA = ":banca";
    const QString CAP = ":id_cap";
    const QString CCIAA = ":cciaa";
    const QString CEL = ":cel";
    const QString CITTA = ":id_citta";
    const QString CLIENTE = ":cliente";
    const QString COD_ART = ":cod_articolo";
    const QString COD_EAN = ":cod_barre";
    const QString COD_FISCALE = ":cod_fisc";
    const QString COD_FRN = ":cod_fornitore";
    const QString COD_IVA = ":cod_iva";
    const QString CONTO = ":conto";
    const QString COGNOME = ":cognome";
    const QString DATA_ARRIVO    = ":data_arrivo";
    const QString DESCR   = ":descr";
    const QString DEST_MERCE = ":dest_merce";
    const QString EMAIL = ":email";
    const QString FATTURA = ":fattura";
    const QString FAX = ":fax";
    const QString FORNITORE = ":fornitore";
    const QString IBAN = ":iban";
    const QString ID = ":id";
    const QString ID_ART  = ":id_articolo";
    const QString ID_FORN = ":id_fornitore";
    const QString ID_MARC = ":id_marca";
    const QString ID_MERC = ":id_merce";
    const QString ID_SEDE = ":id_sede_magazzino";
    const QString ID_UM   = ":id_unita_merce";
    const QString INDIRIZZO = ":indirizzo";
    const QString ISCR_TRIB = ":iscr_trib";
    const QString IVA     = ":iva";
    const QString LOGO = ":logo";
    const QString MODELLO = ":modello";
    const QString NOME = ":nome";
    const QString NOTE = ":note";
    const QString PROVINCIA = ":id_provincia";
    const QString PRT_IVA = ":prt_iva";
    const QString PRZ_ACQ = ":prezzo_acquisto";
    const QString PRZ_FAT = ":prezzo_fattura";
    const QString PRZ_FIN = ":prezzo_finito";
    const QString PRZ_VEN = ":prezzo_vendita";
    const QString QUANTIT = ":quantita";
    const QString RAG_SOCIALE = ":rag_sociale";
    const QString REG_IMPRESE = ":reg_imprese";
    const QString RICARIC = ":ricarico";
    const QString SCONTO  = ":sconto_fornitore";
    const QString SCORTA  = ":scorta_minima";
    const QString SITO_WEB = ":sito_web";
    const QString STATO = ":id_stato";
    const QString SWIFT = ":swift";
    const QString TEL = ":tel";
    const QString TIPO_DITTA = ":id_tipo_ditta";

    //PLACEHOLDER SQL
    const QString DATE = ":date";
    const QString ENT_CASSA = ":ent_cassa";
    const QString ENT_BANCA = ":ent_banca";
    const QString USC_CASSA = ":usc_cassa";
    const QString USC_BANCA = ":usc_banca";
}

#endif // GESTIONALE_CONST_H
