#ifndef PRIMANOTA_CONST
#define PRIMANOTA_CONST

#include <QString>

namespace primanota {
    //CSS
    const QString positive_css = "QLabel {color:blue}";
    const QString negative_css = "QLabel {color:red}";

    //Costanti di configurazione
    const QString SPLITTER_SIZE = "primanota.splitter";
    const QString WINDOW_SIZE = "primanota.window.size";

    //SQL
    //Select tabella prima nota per la table view
    //const QString SELECT_ALL = "SELECT * FROM vw_prima_nota";
    const QString SELECT_ALL =
            "SELECT id AS \"Id\","
                   "data AS \"Data\","
                   "descr AS \"Descrizione\","
                   "entrata_cassa::money AS \"Entrata Cassa\","
                   "uscita_cassa::money AS \"Uscita Cassa\","
                   "entrata_banca::money AS \"Entrata Banca\","
                   "uscita_banca::money AS \"Uscita Banca\""
            "FROM prima_nota";

    //ORDER FILTER usato per ordinare la table view
    const QString ORDER_BY = " ORDER BY \"data\", \"descr\"";

    //SEARCH FILTER usato per la ricerca nella table view
    const QString SEARCH_STR = "\"descr\" ILIKE '%%1%'";

    //MONTH FILTER
    const QString MONTH_STR = "EXTRACT (MONTH FROM \"data\") = '%1' AND EXTRACT (YEARS FROM \"data\") = '%2'";

    //YEARS FILTER
    const QString YEARS_STR = "EXTRACT (YEARS FROM \"data\") = '%1'";

    //RANGE FILTER
    const QString RANGE_STR = "\"data\" >= '%1' AND \"data\" <= '%2'";

    //Effettua la somma delle colonne entrate e uscite
    //utilizzata nelle label della finestra principale
    const QString SELECT_SUM = "SELECT sum(entrata_cassa)::money, "
                                      "sum(entrata_banca)::money,"
                                      "sum(uscita_cassa)::money,"
                                      "sum(uscita_banca)::money "
                               "FROM prima_nota";

    //DELETE per tabella prima_nota
    const QString DELETE_NOTE = "DELETE FROM prima_nota WHERE id = :id";

    //INSERT utilizzata in PrimaNotaAddDialog
    const QString INSERT_NOTE = "INSERT INTO prima_nota(data,"
                                                       "descr,"
                                                       "entrata_cassa,"
                                                       "entrata_banca,"
                                                       "uscita_cassa,"
                                                       "uscita_banca)"
                                "VALUES(:date,"
                                       ":descr,"
                                       ":ent_cassa,"
                                       ":ent_banca,"
                                       ":usc_cassa,"
                                       ":usc_banca)";

    //UPDATE utilizzata in PrimaNotaAddDialog
    const QString UPDATE_NOTE = "UPDATE prima_nota SET data=:date,"
                                                      "descr=:descr,"
                                                      "entrata_cassa=:ent_cassa,"
                                                      "entrata_banca=:ent_banca,"
                                                      "uscita_cassa=:usc_cassa,"
                                                      "uscita_banca=:usc_banca "
                                "WHERE id=:id";

    //SELECT utilizzata nel combobox in PrimaNotaAddDialog
    const QString SELECT_DESCR = "SELECT DISTINCT descr FROM prima_nota ORDER BY descr";

    //SELECT utilizzata in PrimaNotaAddDialog per recuperare i
    //valori della nota selezionata
    //const QString SELECT_FROM_ID = "SELECT * FROM prima_nota WHERE id=:id";
    const QString SELECT_FROM_ID = "SELECT * FROM prima_nota WHERE id=:id";

    //Nome colonne vista noteTableView
    const QString COL_VW_ID = "Id";
    const QString COL_VW_DATA = "Data";
    const QString COL_VW_DESCR = "Descrizione";
    const QString COL_VW_ENT_CASSA = "Entrata Cassa";
    const QString COL_VW_USC_CASSA = "Uscita Cassa";
    const QString COL_VW_ENT_BANCA = "Entrata Banca";
    const QString COL_VW_USC_BANCA = "Uscita Banca";

    //Nome colonne della tabella prima_nota
    const QString COL_DB_ID = "id";
    const QString COL_DB_DATA = "data";
    const QString COL_DB_DESCR = "descr";
    const QString COL_DB_ENT_CASSA = "entrata_cassa";
    const QString COL_DB_USC_CASSA = "uscita_cassa";
    const QString COL_DB_ENT_BANCA = "entrata_banca";
    const QString COL_DB_USC_BANCA = "uscita_banca";

    //PLACEHOLDER SQL
    const QString PH_ID = ":id";
    const QString PH_DATE = ":date";
    const QString PH_DESCR = ":descr";
    const QString PH_ENT_CASSA = ":ent_cassa";
    const QString PH_ENT_BANCA = ":ent_banca";
    const QString PH_USC_CASSA = ":usc_cassa";
    const QString PH_USC_BANCA = ":usc_banca";
}

#endif // PRIMANOTA_CONST

