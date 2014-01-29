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

namespace magazzino {
    const QString SELECT_ARTICOLI_ALL = "SELECT * FROM vw_magazzino";
    const QString SELECT_ARTICOLI_FORNITORE = "SELECT * FROM vw_magazzino WHERE \"Fornitore\" = '%1'";
    const QString SELECT_ARTICOLI_MARCA = "SELECT * FROM vw_magazzino WHERE \"Marca\"= '%1'";
    const QString SELECT_ARTICOLI_CATEGORIA = "SELECT * FROM vw_magazzino WHERE \"Cat.Merce\" = '%1'";
    const QString SELECT_ARTICOLI_SEDE = "SELECT * FROM vw_magazzino WHERE \"Sede Magazzino\" = '%1'";
    const QString SELECT_FILTER = "SELECT id, descr FROM %1";
    const QString SELECT_FILTER_FORNITORI = "SELECT \"Id\" as id, \"Ragione sociale\" as descr FROM vw_anagrafica_fornitori";
    const QString SELECT_STORICO = "SELECT * FROM vw_listino_storico WHERE \"Id Articolo\"='%1' ORDER BY \"Data\" DESC, \"Imponibile\" DESC";
    const QString DELETE_ARTICOLO = "DELETE FROM magazzino WHERE id = :id";

    const QString SELECT_FORNITORE = "SELECT \"Id\", \"Ragione sociale\" from vw_anagrafica_fornitori ORDER BY \"Ragione sociale\"";
    const QString INSERT_ARTICOLO = "INSERT INTO magazzino (descr, id_fornitore, id_marca, modello, cod_articolo, cod_fornitore, cod_barre ,id_merce ,id_cod_iva, id_unita_misura, scorta_minima, quantita, prezzo_acquisto, sconto_fornitore, ricarico, imponibile, iva, prezzo_finito, prezzo_vendita, fattura, data_arrivo, id_sede_magazzino, note) VALUES (:descr, :id_fornitore, :id_marca, :modello, :cod_articolo, :cod_fornitore, :cod_barre, :id_merce, :id_cod_iva, :id_unita_merce, :scorta_minima, :quantita, :prezzo_acquisto, :sconto_fornitore, :ricarico, :imponibile, :iva, :prezzo_finito, :prezzo_vendita, :fattura, :data_arrivo, :id_sede_magazzino, :note)";
    const QString INSERT_STORICO = "INSERT INTO listino_storico (id_articolo, data_arrivo, quantita, prezzo_acquisto, sconto_fornitore, ricarico, imponibile, iva, prezzo_finito, prezzo_vendita, fattura) VALUES (:id_articolo, :data_arrivo, :quantita, :prezzo_acquisto, :sconto_fornitore, :ricarico, :imponibile, :iva, :prezzo_finito, :prezzo_vendita, :fattura)";
    const QString SELECT_FROM_ID = "SELECT * FROM magazzino WHERE id = :id";
    const QString UPDATE_ARTICOLO = "UPDATE magazzino SET descr=:descr, id_fornitore=:id_fornitore, id_marca=:id_marca, modello=:modello, cod_articolo=:cod_articolo, cod_fornitore=:cod_fornitore, cod_barre=:cod_barre, id_merce=:id_merce, id_cod_iva=:id_cod_iva, id_unita_misura=:id_unita_merce, scorta_minima=:scorta_minima, quantita=:quantita, prezzo_acquisto=:prezzo_acquisto, sconto_fornitore=:sconto_fornitore, ricarico=:ricarico, imponibile=:imponibile, iva=:iva, prezzo_finito=:prezzo_finito, prezzo_vendita=:prezzo_vendita, fattura=:fattura, data_arrivo=:data_arrivo, id_sede_magazzino=:id_sede_magazzino, note=:note WHERE id=:id";

    enum columns {COL_ID,
                  COL_DESCR = 1,
                  COL_ID_FORN,
                  COL_ID_MARCA,
                  COL_MODELLO,
                  COL_COD_ART,
                  COL_COD_FOR,
                  COL_COD_EAN,
                  COL_ID_MERCE,
                  COL_ID_COD_IVA,
                  COL_ID_UM,
                  COL_SCORTA,
                  COL_QUANTITA,
                  COL_PREZZO_ACQ,
                  COL_SCONTO,
                  COL_RICARICO,
                  COL_IMPONIBILE,
                  COL_IVA,
                  COL_PREZZO_FIN,
                  COL_PREZZO_VEN,
                  COL_FATTURA,
                  COL_DATA,
                  COL_ID_SEDE,
                  COL_NOTE};
}

#endif // ENUM_CONST_H
