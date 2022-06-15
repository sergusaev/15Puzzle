#ifndef DBCONNECTIONMANAGER_H
#define DBCONNECTIONMANAGER_H

#include <memory>
#include <QObject>
#include <dbtypes.h>
#include "dbmanager.h"

namespace db
{
class ConnectionManager
{
public:
    Q_DISABLE_COPY(ConnectionManager)
    ConnectionManager(DBTypes::DBManagerType managerType);
    ~ConnectionManager();
    std::string databasePath() const;
    DBTypes::DBState state() const;
    bool isValid() const;

private:
    std::unique_ptr<DBManager> m_d;
};
}
#endif // DBCONNECTIONMANAGER_H
