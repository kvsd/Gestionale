#ifndef DOCUMENTI_CONST_H
#define DOCUMENTI_CONST_H

namespace documenti {

    const QString SELECT_DOC_ALL = "SELECT id AS \"Id\", "
                                   "       id_cliente AS \"Cliente\" "
                                   "FROM documenti";

    //Utilizzato nel combobox cliente di DocumentiAddDialog.
    const QString SELECT_CLIENTE = "SELECT id, concat(rag_sociale, cognome, nome) AS rag_sociale "
                                   "FROM anagrafica";

}
#endif // DOCUMENTI_CONST_H
