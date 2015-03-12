#ifndef DB_CONST
#define DB_CONST

#include <QString>

namespace dbconst {
    //SETTINGS
    const QString DEFAULT_DB = "user";
    const QString DEFAULT_HOST = "localhost";
    const int DEFAULT_PORT = 5432;

    const QString dbname = "dbname";
    const QString hostname = "hostname";
    const QString port = "port";


    //SQL
    const QString SELECT_USERS = "SELECT name FROM user_db";

    //CAMPI SQL
    const QString name = "name";
}

#endif // DB_CONST

