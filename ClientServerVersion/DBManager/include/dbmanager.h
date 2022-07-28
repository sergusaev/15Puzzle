#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <QSqlDatabase>
#include <dbtypes.h>

namespace db
{

    class DBCloser {
    public:
        void operator() (QSqlDatabase* db) {
            db->close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        }
    };


class DBManager {
public:


    std::unique_ptr<QSqlDatabase, DBCloser> m_database;
    virtual ~DBManager() = default;
    DBTypes::DBState m_state {DBTypes::DBState::OK};
    bool m_isValid {true};

    bool setUp();
    bool setUpWorkspace();
    bool setUpTables();
    void setIsValid(bool isValid);

    virtual QString getDatabaseName() = 0;
    virtual std::vector<QSqlQuery> getCreationQueries() = 0;

    std::string m_dbPath;

};

}

#endif //DBMANAGER_H
