#ifndef DBMANAGERCLIENT_H
#define DBMANAGERCLIENT_H

#include "dbmanager.h"
#include <QSqlQuery>

namespace db
{
class DBManagerClient : public DBManager {
    virtual void setDatabaseName() override;
    virtual void setCreationQueries() override;
};


}
#endif // DBMANAGERCLIENT_H
