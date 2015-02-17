#ifndef PRIMANOTA_CONST
#define PRIMANOTA_CONST

#include <QString>

namespace primanota {
    //CSS
    const QString positive_css = "QLabel {color:blue}";
    const QString negative_css = "QLabel {color:red}";

    //Costanti di configurazione
    const QString SPLITTER_SIZE = "primanota.splitter";

    //SQL
    //Select tabella prima nota per la table view
    const QString SELECT_ALL = "SELECT * FROM vw_prima_nota ORDER BY \"Data\"";

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

    //SELECT utilizzata nel combobox in PrimaNotaAddDialog
    const QString SELECT_DESCR = "SELECT DISTINCT descr FROM prima_nota ORDER BY descr";



    enum Column {
        COL_ID = 0,
        COL_DATA = 1,
        COL_DESCR = 2,
        COL_ENT_CASSA = 3,
        COL_USC_CASSA = 4,
        COL_ENT_BANCA = 5,
        COL_USC_BANCA = 6
    };

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

