#ifndef AZIENDA_CONST_H
#define AZIENDA_CONST_H

#include <QString>

namespace azienda {

    const QString SELECT_QUERY = "SELECT * FROM azienda WHERE id=0";
    const QString UPDATE_QUERY = "UPDATE azienda SET "
                                     "rag_sociale=:rag_sociale, "
                                     "nome=:nome, "
                                     "cognome=:cognome, "
                                     "prt_iva=:prt_iva, "
                                     "cod_fisc=:cod_fisc, "
                                     "id_reg_fiscale=:id_reg_fiscale, "
                                     "id_provincia_rea=:id_provincia_rea, "
                                     "numero_rea=:numero_rea, "
                                     "id_stato_liquid=:id_stato_liquid, "
                                     "indirizzo=:indirizzo, "
                                     "id_citta=:id_citta, "
                                     "id_provincia=:id_provincia, "
                                     "id_cap=:id_cap, "
                                     "id_stato=:id_stato, "
                                     "tel=:tel, "
                                     "fax=:fax, "
                                     "email=:email, "
                                     "pec=:pec,"
                                     "logo=:logo "
                                 "WHERE id=0";
}
#endif // AZIENDA_CONST_H
