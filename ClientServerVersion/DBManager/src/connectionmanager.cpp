#include "connectionmanager.h"
#include "dbmanagerclient.h"
#include "dbmanagerserver.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>


namespace db
{



std::string ConnectionManager::databasePath() const
{
    return m_d->m_dbPath;
}

DBTypes::DBState ConnectionManager::state() const
{
    return m_d->m_state;
}


bool ConnectionManager::isValid() const
{
    return m_d->m_isValid && m_d->m_database->isValid();
}

ConnectionManager::ConnectionManager(DBTypes::DBManagerType managerType)

{
    switch (managerType) {
    case DBTypes::DBManagerType::CLIENT:
        m_d = std::unique_ptr<DBManager>(new DBManagerClient {});
        break;
    case DBTypes::DBManagerType::SERVER:
        m_d  = std::unique_ptr<DBManager>(new DBManagerServer {});
        break;
    }

    const bool setupResult {m_d->setUp()};
    m_d->setIsValid(setupResult);
}

ConnectionManager::~ConnectionManager()
{
}
}
