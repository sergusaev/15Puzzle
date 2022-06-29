#include "dbmanagerclient.h"

namespace db {

QString DBManagerClient::getDatabaseName()
{
    return "ClientCacheRecordsDB";
}

std::vector<QSqlQuery> DBManagerClient::getCreationQueries()
{
    return {
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
