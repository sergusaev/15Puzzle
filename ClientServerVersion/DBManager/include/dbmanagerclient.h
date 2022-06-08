#ifndef DBMANAGERCLIENT_H
#define DBMANAGERCLIENT_H

#include "dbmanager.h"
#include <QSqlQuery>

class DBManagerClient : public DBManager {
    virtual void setDatabaseName() override;
    virtual void setCreationQueries() override;
};

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

#endif // DBMANAGERCLIENT_H
