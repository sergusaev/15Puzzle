#include "dbmanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDir>

namespace db{

bool DBManager::setUp()
{
    const QString driver {"QSQLITE"};

    if (!QSqlDatabase::isDriverAvailable(driver))
    {
        m_state = DBTypes::DBState::ERROR_NO_DRIVER;
        qWarning() << "Driver " << driver << " is not available.";
        return false;
    }

    if (!setUpWorkspace())
    {
        m_state = DBTypes::DBState::ERROR_WORKSPACE;
        qCritical() << "Workspace setup failed!";
        return false;
    }

    auto* db = new QSqlDatabase {QSqlDatabase::addDatabase(driver)};
    m_database.reset(db);
    m_database->setDatabaseName(QString::fromStdString(m_dbPath));

    qDebug() << "Database name: " << m_database->databaseName();

    if (!m_database->open())
    {
        m_state = DBTypes::DBState::ERROR_OPENING;
        qCritical() << "Error in opening DB " << m_database->databaseName()
                   << " reason: " <<  m_database->lastError().text();
        return false;
    }

    return setUpTables();
}

bool DBManager::setUpWorkspace()
{
    const QString location {QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)};
    const QString fullPath {location + "/" + getDatabaseName()};

    m_dbPath = fullPath.toStdString();

    QDir dbDirectory {location};
    if (!dbDirectory.exists())
    {
        const bool creationResult {dbDirectory.mkpath(location)};
        qWarning() << "DB directory not exist, creating result: "
                   << creationResult;
    }

    qDebug() << "Data path: " << fullPath;

    return dbDirectory.exists();
}

bool DBManager::setUpTables()
{
    bool result {true};

    for (auto& query : getCreationQueries())
    {
        if (!query.exec())
        {
            result = false;
            m_state = DBTypes::DBState::ERROR_TABLES;
            qWarning() << "Table creation failed. Reason: "
                       << query.lastError();
        }
        else
        {
            qWarning() << "Table successfully opened or created. Query: " << query.lastQuery();
        }
    }

    return result;
}

void DBManager::setIsValid(bool isValid)
{
    m_isValid = isValid;
}

}
