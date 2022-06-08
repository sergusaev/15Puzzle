#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <QSqlDatabase>
#include <dbtypes.h>


namespace
{
    class DBCloser {
    public:
        void operator() (QSqlDatabase* db) {
            db->close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        }
    };
}

class DBManager {
public:
    std::unique_ptr<QSqlDatabase, DBCloser> m_database;

    DBTypes::DBState m_state {DBTypes::DBState::OK};
    bool m_isValid {true};

    bool setUp();
    bool setUpWorkspace();
    bool setUpTables();
    void setIsValid(bool isValid);

    virtual void setDatabaseName() = 0;
    virtual void setCreationQueries() = 0;

    std::string m_dbPath;
    QString m_databaseName;
    std::vector<QSqlQuery> m_creationQueries;
};



#endif //DBMANAGER_H
