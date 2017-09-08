#ifndef AGENTI_CONST_H
#define AGENTI_CONST_H

namespace agenti {
    //Query usata da AgentiAddDialog per aggiungere un nuovo record
    const QString INSERT_QUERY = "INSERT INTO agenti(nome,"
                                                    "cognome,"
                                                    "tel,"
                                                    "fax,"
                                                    "cel,"
                                                    "email) "
                                   "VALUES(:nome, "
                                          ":cognome, "
                                          ":tel, "
                                          ":fax,"
                                          ":cel, "
                                          ":email)";

    //Query usata da AgentiViewDialog per cancellare un record
    const QString DELETE_QUERY = "DELETE FROM agenti WHERE id=:id";

    //Query usata da AgentiAddDialog per aggiornare un record
    const QString UPDATE_QUERY = "UPDATE agenti "
                                 "SET nome=:nome, "
                                     "cognome=:cognome, "
                                     "tel=:tel, "
                                     "fax=:fax, "
                                     "cel=:cel, "
                                     "email=:email "
                                 "WHERE id=:id";

    //Query usata per caricare i dati in AgentiAddDialog
    const QString SELECT_FROM_ID = "SELECT * FROM agenti WHERE id=:id";

    //Query usata da AgentiViewDialog per elencare tutti gli agenti
    const QString SELECT_AGENTI = "SELECT "
                                      "id AS \"Id\","
                                      "nome AS \"Nome\","
                                      "cognome AS \"Cognome\","
                                      "tel AS \"Telefono\","
                                      "fax AS \"Fax\", "
                                      "cel AS \"Cellulare\", "
                                      "email AS \"Email\" "
                                  "FROM agenti "
                                  "WHERE id>0 ";

    const QString ORDER_CLAUSE = "ORDER BY cognome";

    const QString SEARCH_CLAUSE =  "AND \"cognome\" ILIKE '\%%1\%' ";


    //SETTINGS
    const QString CSS_WARNING_STYLE = "background-color: yellow";
    const QString WINDOW_SIZE = "AgentiViewDlg.size";
}

#endif // AGENTI_CONST_H

