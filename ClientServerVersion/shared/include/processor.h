#ifndef PROCESSOR_H
#define PROCESSOR_H


#include "dbtypes.h"
#include "../../DBManager/include/executor.h"
#include <memory>

namespace db
{

class Processor
{
public:
    Processor(DBTypes::DBManagerType managerType);

    //manipulator methods

    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTableData(DBTypes::DBTables table);
    DBTypes::DBResult insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData);
    DBTypes::DBResult insertRowMultiple(const std::string& tableName, const DBTypes::DBEntry& recordData, int paramCount);

    DBTypes::DBResult deleteFirst(const std::string& tableName);
    DBTypes::DBResult deleteAll(const std::string& tableName);

    //selector methods
    DBTypes::DBResult selectAll(const std::string& tableName, std::vector<QVariantList>& returnData);
    DBTypes::DBResult selectFirst(const std::string& tableName, QVariantList& returnData);
    DBTypes::DBResult selectTopTime(const std::string& tableName, int dimension, std::vector<QVariantList>& returnData);
    DBTypes::DBResult selectTopTurns(const std::string& tableName, int dimension, std::vector<QVariantList>& returnData);
    DBTypes::DBResult selectUserPassword(const std::string& username, QVariant& returnData);
private:
    Executor m_executor;

    //manipulator methods
    std::string generateBindString(int paramCount) const;
    std::string generateInsertQuery(const std::string& tableName, int paramCount) const;
    std::string generateMultipleInsertQuery(const std::string& tableName, int paramCount, int multiplier) const;

    //selector methods
    std::string generateSelectAllQuery(const std::string& tableName) const;
    std::string generateSelectTopTimeQuery(const std::string& tableName) const;
    std::string generateSelectTopTurnsQuery(const std::string& tableName) const;
};

}

#endif // PROCESSOR_H
