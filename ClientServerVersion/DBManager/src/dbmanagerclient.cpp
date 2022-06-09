#include "dbmanagerclient.h"

namespace db {

void DBManagerClient::setDatabaseName()
{
    m_databaseName  = "ClientDB";
}

void DBManagerClient::setCreationQueries()
{
    m_creationQueries = {
        QSqlQuery {
            "CREATE TABLE IF NOT EXISTS RecordsCache"
            "("
            "Nickname TEXT NOT NULL,"
            "Time INTEGER NOT NULL,"
            "Turns INTEGER NOT NULL,"
            "Dimension INTEGER NOT NULL"
            ")"
        }
    };
}


}
