#ifndef PRIMANOTA_CONST
#define PRIMANOTA_CONST

#include <QString>

namespace primanota {

    //Costanti di configurazione
    const QString SPLITTER_SIZE = "primanota.splitter";

    //Select principale per la table view
    const QString SELECT_ALL = "SELECT * FROM vw_prima_nota";

    enum Column {
        COL_ID = 0,
        COL_DESCR = 1,
        COL_ENT_CASSA = 2,
        COL_USC_CASSA = 3,
        COL_ENT_BANCA = 4,
        COL_USC_BANCA = 5
    };
}

#endif // PRIMANOTA_CONST

