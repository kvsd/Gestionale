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
    const QString SELECT_ALL = "SELECT * FROM vw_prima_nota";

    //Effettua la somma delle colonne entrate e uscite
    //utilizzata nelle label della finestra principale
    const QString SELECT_SUM = "SELECT sum(entrata_cassa)::money, "
                                      "sum(entrata_banca)::money,"
                                      "sum(uscita_cassa)::money,"
                                      "sum(uscita_banca)::money "
                               "FROM prima_nota";

    //DELETE per tabella prima_nota
    const QString DELETE_NOTE = "DELETE FROM prima_nota WHERE id = :id";


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
}

#endif // PRIMANOTA_CONST

