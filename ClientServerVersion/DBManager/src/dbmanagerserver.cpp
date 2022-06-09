#include "dbmanagerserver.h"

namespace db {

void DBManagerServer::setDatabaseName()
{
    m_databaseName  = "ServerDB";
}

void DBManagerServer::setCreationQueries()
{
    m_creationQueries = {
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
