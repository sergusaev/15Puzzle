#ifndef DBMANAGERSERVER_H
#define DBMANAGERSERVER_H

#include "dbmanager.h"
#include <QSqlQuery>

class DBManagerServer : public DBManager {
    virtual void setDatabaseName() override;
    virtual void setCreationQueries() override;
};

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


#endif // DBMANAGERSERVER_H
