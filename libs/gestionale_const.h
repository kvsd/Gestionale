#ifndef GESTIONALE_CONST_H
#define GESTIONALE_CONST_H

#include <QString>

namespace table {
    //Nome tabelle database
    const QString AGENTI = "agenti";
    const QString ANAGRAFICA = "anagrafica";
    const QString ASPETTO_BENI = "aspetto_beni";
    const QString AZIENDA = "azienda";
    const QString CAP = "cap";
    const QString CASUALE_TRASPORTO = "casuale_trasporto";
    const QString CATEGORIA_MERCE = "cat_merce";
    const QString CITTA = "citta";
    const QString CODICE_IVA = "cod_iva";
    const QString LISTINO_STORICO = "listino_storico";
    const QString MAGAZZINO = "magazzino";
    const QString MARCA = "marca";
    const QString MONETA = "moneta";
    const QString PROVINCIA = "provincia";
    const QString REG_FISCALE = "reg_fiscale";
    const QString SEDE_MAGAZZINO = "sede_magazzino";
    const QString STATO = "stato";
    const QString STATO_LIQUID = "stato_liquid";
    const QString TIPO_DOCUMENTO = "tipo_documento";
    const QString TIPO_PAGAMENTO = "tipo_pagamento";
    const QString TIPO_TRASMISSIONE = "trasmissione";
    const QString UNITA_MISURA = "unita_misura";
    const QString USER_DB = "user_db";
    const QString VETTORE = "vettore";
}

namespace ph {
    //placeholder per query sql
    const QString CLIENTE = ":cliente";
    const QString COD_FISCALE = ":cod_fisc";
    const QString CODICE_IVA = ":cod_iva";
    const QString DATE = ":date";
    const QString DATA_ARRIVO    = ":data_arrivo";
    const QString DESCRIZIONE   = ":descr";
    const QString ENT_BANCA = ":entrata_banca";
    const QString ENT_CASSA = ":entrata_cassa";
    const QString FATTURA = ":fattura";
    const QString FORNITORE = ":fornitore";
    const QString ID = ":id";
    const QString ID_ART  = ":id_articolo";
    const QString IVA     = ":iva";
    const QString LOGO = ":logo";
    const QString PRT_IVA = ":prt_iva";
    const QString PRZ_ACQ = ":prezzo_acquisto";
    const QString PRZ_FAT = ":prezzo_fattura";
    const QString PRZ_FIN = ":prezzo_finito";
    const QString PRZ_VEN = ":prezzo_vendita";
    const QString PRZ_VEN_B = ":prezzo_vendita_b";
    const QString QUANTIT = ":quantita";
    const QString RICARIC = ":ricarico";
    const QString SCONTO  = ":sconto_fornitore";
    const QString SCORTA  = ":scorta_minima";
    const QString USC_CASSA = ":uscita_cassa";
    const QString USC_BANCA = ":uscita_banca";
}

namespace coldb {
    //Nome colonne database
    const QString AGENZIA = "agenzia";
    const QString AZIENDA = "azienda";
    const QString BANCA = "banca";
    const QString CEL = "cel";
    const QString CLIENTE = "cliente";
    const QString CODICE_ARTICOLO = "cod_articolo";
    const QString CODICE_BARRE = "cod_barre";
    const QString CODICE_FISCALE = "cod_fisc";
    const QString CODICE_FORNITORE = "cod_fornitore";
    const QString CODICE_IVA = "cod_iva";
    const QString COD_SDI = "cod_sdi";
    const QString COGNOME = "cognome";
    const QString CONTO = "conto";
    const QString DATA = "data";
    const QString DATA_ARRIVO = "data_arrivo";
    const QString DESCRIZIONE = "descr";
    const QString DESTINAZIONE_MERCE = "dest_merce";
    const QString EMAIL = "email";
    const QString ENT_BANCA = "entrata_banca";
    const QString ENT_CASSA = "entrata_cassa";
    const QString FAX = "fax";
    const QString FATTURA = "fattura";
    const QString FORNITORE = "fornitore";
    const QString IBAN = "iban";
    const QString ID = "id";
    const QString ID_AGENTE = "id_agente";
    const QString ID_ARTICOLO = "id_articolo";
    const QString ID_CAP = "id_cap";
    const QString ID_CITTA = "id_citta";
    const QString ID_FORNITORE = "id_fornitore";
    const QString ID_MARCA = "id_marca";
    const QString ID_MERCE = "id_merce";
    const QString ID_PROVINCIA = "id_provincia";
    const QString ID_PROVINCIA_REA = "id_provincia_rea";
    const QString ID_REG_FISCALE = "id_reg_fiscale";
    const QString ID_SEDE_MAGAZZINO = "id_sede_magazzino";
    const QString ID_STATO = "id_stato";
    const QString ID_STATO_LIQUID = "id_stato_liquid";
    const QString ID_TRASMISSIONE = "id_trasmissione";
    const QString ID_UNITA = "id_unita_misura";
    const QString INDIRIZZO = "indirizzo";
    const QString IVA = "iva";
    const QString LOGO = "logo";
    const QString MODELLO = "modello";
    const QString NOME = "nome";
    const QString NOTE = "note";
    const QString NUMERO_REA = "numero_rea";
    const QString PA = "pa";
    const QString PARTITA_IVA = "prt_iva";
    const QString PEC = "pec";
    const QString PREZZO_ACQUISTO = "prezzo_acquisto";
    const QString PREZZO_FATTURA = "prezzo_fattura";
    const QString PREZZO_FINITO = "prezzo_finito";
    const QString PREZZO_VENDITA = "prezzo_vendita";
    const QString PREZZO_VENDITA_B = "prezzo_vendita_b";
    const QString QUANTITA = "quantita";
    const QString RAGIONE_SOCIALE = "rag_sociale";
    const QString RICARICO = "ricarico";
    const QString SCONTO_FORNITORE = "sconto_fornitore";
    const QString SCORTA_MINIMA = "scorta_minima";
    const QString SITO_WEB = "sito_web";
    const QString SWIFT = "swift";
    const QString TEL = "tel";
    const QString USC_BANCA = "uscita_banca";
    const QString USC_CASSA = "uscita_cassa";
}

namespace colview {
//Nome colonne tableview/tablewidget
//const QString AGENZIA = "agenzia";
//const QString BANCA = "banca";
//const QString CEL = "cel";
//const QString CLIENTE = "cliente";
const QString CODICE_ARTICOLO = "Cod.Articolo";
const QString CODICE_BARRE = "Cod.EAN";
//const QString CODICE_FISCALE = "cod_fisc";
const QString CODICE_FORNITORE = "Cod.Fornitore";
const QString CODICE_IVA = "Cod.IVA";
//const QString COGNOME = "cognome";
//const QString CONTO = "conto";
const QString DATA = "Data";
const QString DATA_ARRIVO = "Data Arrivo";
const QString DESCRIZIONE = "Descrizione";
//const QString DESTINAZIONE_MERCE = "dest_merce";
//const QString EMAIL = "email";
const QString ENT_BANCA = "Entrata Banca";
const QString ENT_CASSA = "Entrata Cassa";
//const QString FAX = "fax";
const QString FATTURA = "Nr.Fattura";
const QString FORNITORE = "Fornitore";
//const QString IBAN = "iban";
const QString ID = "Id";
//const QString ID_AGENTE = "id_agente";
//const QString ID_ARTICOLO = "id_articolo";
//const QString ID_CAP = "id_cap";
//const QString ID_CITTA = "id_citta";
//const QString ID_FORNITORE = "id_fornitore";
//const QString ID_MARCA = "id_marca";
//const QString ID_MERCE = "id_merce";
//const QString ID_PROVINCIA = "id_provincia";
//const QString ID_SEDE_MAGAZZINO = "id_sede_magazzino";
//const QString ID_STATO = "id_stato";
//const QString ID_UNITA = "id_unita_misura";
//const QString INDIRIZZO = "indirizzo";
const QString IVA = "Iva";
const QString MODELLO = "Modello";
//const QString NOME = "nome";
const QString NOTE = "Note";
//const QString PARTITA_IVA = "prt_iva";
const QString PREZZO_ACQUISTO = "Prezzo Acquisto";
const QString PREZZO_FATTURA = "Prezzo Fattura";
const QString PREZZO_FINITO = "Prezzo Finito";
const QString PREZZO_VENDITA = "Prezzo Vendità";
const QString PREZZO_VENDITA_B = "Prezzo Vendità B";
const QString QUANTITA = "Quantità";
//const QString RAGIONE_SOCIALE = "rag_sociale";
const QString RICARICO = "Ricarico";
const QString SCONTO_FORNITORE = "Sconto Fornitore";
const QString SCORTA_MINIMA = "Scorta Minima";
//const QString SITO_WEB = "sito_web";
//const QString SWIFT = "swift";
//const QString TEL = "tel";
const QString USC_BANCA = "Uscita Banca";
const QString USC_CASSA = "Uscita Cassa";
}

namespace css {
    //CSS
    const QString positive = "QLabel {color:blue}";
    const QString negative = "QLabel {color:red}";
    const QString warning = "QLineEdit {background-color:yellow}";
    const QString warning_cb = "QComboBox {background-color:yellow;}";
    const QString warning_ckb = "QCheckBox {background-color:yellow}";
    const QString warning_rb = "QRadioButton {background-color:yellow}";
}

#endif // GESTIONALE_CONST_H
