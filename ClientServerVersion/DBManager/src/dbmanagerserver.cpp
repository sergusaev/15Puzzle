#include "dbmanagerserver.h"

namespace db {


QString DBManagerServer::getDatabaseName()
{
    return "ServerDB";
}

std::vector<QSqlQuery> DBManagerServer::getCreationQueries()
{
    return {
        QSqlQuery {
            "CREATE TABLE IF NOT EXISTS Records"
            "("
            "Nickname TEXT NOT NULL,"
            "Time INTEGER NOT NULL,"
            "Turns INTEGER NOT NULL,"
            "Dimension INTEGER NOT NULL"
            ")"
        },
        QSqlQuery {
            "CREATE TABLE IF NOT EXISTS Users"
            "("
            "Nickname TEXT NOT NULL,"
            "Password TEXT NOT NULL,"
            "UNIQUE(Nickname)"
            ")"
        }
    };
}

}
