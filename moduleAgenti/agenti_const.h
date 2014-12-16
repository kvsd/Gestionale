#ifndef AGENTI_CONST_H
#define AGENTI_CONST_H

namespace agenti {
    //SQL
    const QString SQL_ADD_AGENTE = "INSERT INTO agenti(nome, cognome, tel, fax, cel, email) VALUES(:nome, :cognome, :tel, :fax, :cel, :email)";
    const QString SQL_DELETE_AGENTE = "DELETE FROM agenti WHERE id=:id";
    const QString SQL_UPDATE_AGENTE = "UPDATE agenti SET nome=:nome, cognome=:cognome, tel=:tel, fax=:fax, cel=:cel, email=:email WHERE id=:id";
    const QString SQL_SELECT_AGENTE = "SELECT * FROM agenti WHERE id=:id";

    const QString SQL_SELECT_AGENTI = "SELECT * FROM agenti WHERE id>0 ORDER BY cognome";
    const QString SQL_SEARCH_AGENTI = "SELECT * FROM agenti WHERE \"cognome\" ILIKE '\%%1\%' AND id>0 ORDER BY cognome";

    //SETTINGS
    const QString CSS_WARNING_STYLE = "background-color: yellow";
    const QString WINDOW_SIZE = "AgentiViewDlg.size";

    //CONST
    enum columns {COL_ID,
                  COL_NOME,
                  COL_COGNOME,
                  COL_TEL,
                  COL_FAX,
                  COL_CEL,
                  COL_EMAIL};

    //PH PlaceHolder
    const QString PH_ID = ":id";
    const QString PH_NOME = ":nome";
    const QString PH_COGNOME = ":cognome";
    const QString PH_TEL = ":tel";
    const QString PH_FAX = ":fax";
    const QString PH_CEL = ":cel";
    const QString PH_EMAIL = ":email";
}

#endif // AGENTI_CONST_H

