#ifndef DBMANAGERCLIENT_H
#define DBMANAGERCLIENT_H

#include "dbmanager.h"
#include <QSqlQuery>

namespace db
{

class DBManagerClient : public DBManager {
    virtual QString getDatabaseName() override;
    virtual std::vector<QSqlQuery> getCreationQueries() override;
};


}
#endif // DBMANAGERCLIENT_H
