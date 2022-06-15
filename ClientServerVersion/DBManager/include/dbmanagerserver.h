#ifndef DBMANAGERSERVER_H
#define DBMANAGERSERVER_H

#include "dbmanager.h"
#include <QSqlQuery>

namespace db
{


class DBManagerServer : public DBManager {
    virtual QString getDatabaseName() override;
    virtual std::vector<QSqlQuery> getCreationQueries() override;
};



}
#endif // DBMANAGERSERVER_H
