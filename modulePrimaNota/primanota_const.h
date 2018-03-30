#ifndef PRIMANOTA_CONST
#define PRIMANOTA_CONST

#include <QString>

namespace primanota {
    //Select tabella prima nota per la table view
    const QString SELECT_PN =
            "SELECT id AS \"Id\","
                   "data AS \"Data\","
                   "descr AS \"Descrizione\","
                   "entrata_cassa::money AS \"Entrata Cassa\","
                   "uscita_cassa::money AS \"Uscita Cassa\","
                   "entrata_banca::money AS \"Entrata Banca\","
                   "uscita_banca::money AS \"Uscita Banca\""
            "FROM prima_nota";

    //INSERT utilizzata in PrimaNotaAddDialog
    const QString INSERT_PN =
            "INSERT INTO prima_nota(data, descr,entrata_cassa, entrata_banca,"
                                   "uscita_cassa, uscita_banca)"
            "VALUES(:date, :descr, :ent_cassa, :ent_banca, :usc_cassa, :usc_banca)";

    //UPDATE utilizzata in PrimaNotaAddDialog
    const QString UPDATE_PN =
            "UPDATE prima_nota SET data=:date, descr=:descr, entrata_cassa=:ent_cassa,"
                                  "entrata_banca=:ent_banca, uscita_cassa=:usc_cassa,"
                                  "uscita_banca=:usc_banca "
            "WHERE id=:id";

    //DELETE per tabella prima_nota
    const QString DELETE_PN = "DELETE FROM prima_nota WHERE id = :id";

    //SELECT utilizzata in PrimaNotaAddDialog per recuperare i
    //valori della nota selezionata
    const QString SELECT_PN_FROM_ID = "SELECT * FROM prima_nota WHERE id=:id";

    //Effettua la somma delle colonne entrate e uscite
    //utilizzata nelle label della finestra principale
    const QString SELECT_PN_TOTAL = "SELECT sum(entrata_cassa)::money AS entrata_cassa, "
                                           "sum(entrata_banca)::money AS entrata_banca,"
                                           "sum(uscita_cassa)::money AS uscita_cassa,"
                                           "sum(uscita_banca)::money AS uscita_banca "
                                    "FROM prima_nota";

    //SELECT utilizzata nel combobox in PrimaNotaAddDialog
    const QString SELECT_NOTE_DISTINCT = "SELECT DISTINCT descr FROM prima_nota ORDER BY descr";

    //ORDER FILTER usato per ordinare la table view
    const QString PN_ORDER = " ORDER BY \"data\", \"descr\"";

    //SEARCH FILTER usato per la ricerca nella table view
    const QString PN_DESCR = "\"descr\" ILIKE '%%1%'";

    //MONTH FILTER
    const QString PN_MONTH = "EXTRACT (MONTH FROM \"data\") = '%1' AND EXTRACT (YEARS FROM \"data\") = '%2'";

    //YEARS FILTER
    const QString PN_YEARS = "EXTRACT (YEARS FROM \"data\") = '%1'";

    //RANGE FILTER
    const QString PN_RANGE = "\"data\" >= '%1' AND \"data\" <= '%2'";
}

#endif // PRIMANOTA_CONST

