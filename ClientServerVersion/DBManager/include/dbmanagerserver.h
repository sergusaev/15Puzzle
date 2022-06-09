#ifndef DBMANAGERSERVER_H
#define DBMANAGERSERVER_H

#include "dbmanager.h"
#include <QSqlQuery>

namespace db
{


class DBManagerServer : public DBManager {
    virtual void setDatabaseName() override;
    virtual void setCreationQueries() override;
};



}
#endif // DBMANAGERSERVER_H
