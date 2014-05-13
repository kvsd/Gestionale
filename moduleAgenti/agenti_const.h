#ifndef AGENTI_CONST_H
#define AGENTI_CONST_H

namespace agenti {
    const QString ADD_AGENTE = "INSERT INTO agenti(nome, cognome, tel, cel, email) VALUES(:nome, :cognome, :tel, :cel, :email)";
    const QString DELETE_AGENTE = "DELETE FROM agenti WHERE id=:id";
    const QString UPDATE_AGENTE = "UPDATE agenti SET nome=:nome, cognome=:cognome, tel=:tel, cel=:cel, email=:email WHERE id=:id";
    const QString SELECT_AGENTE = "SELECT * FROM agenti WHERE id=:id";

    const QString SELECT_AGENTI = "SELECT * FROM agenti WHERE id>0 ORDER BY cognome";
    const QString SEARCH_AGENTI = "SELECT * FROM agenti WHERE \"cognome\" ILIKE '\%%1\%' AND id>0 ORDER BY cognome";

    const QString CSS_WARNING_STYLE = "background-color: yellow";
    const QString WINDOW_SIZE = "AgentiViewDlg.size";

    enum columns {COL_ID,
                  COL_NOME,
                  COL_COGNOME,
                  COL_TEL,
                  COL_CEL,
                  COL_EMAIL};
}

#endif // AGENTI_CONST_H

