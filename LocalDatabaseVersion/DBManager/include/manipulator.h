#ifndef MANIPULATOR_H
#define MANIPULATOR_H


#include "executor.h"
#include "dbtypes.h"

namespace db
{
class Manipulator
{
public:
    std::pair<DBTypes::DBResult, DBTypes::DBIndex> insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData);
    DBTypes::DBResult removeRow(const std::string& tableName, const DBTypes::DBIndex index);
    DBTypes::DBResult updateRow(const std::string& tableName, const DBTypes::DBIndex indexToUpdate, const DBTypes::DBEntry& updatedRecordData);

private:
    Executor m_executor;
    std::string generateBindString(int paramCount) const;
    std::string generateInsertQuery(const std::string& tableName, int paramCount) const;
    std::string generateRemoveQuery(const std::string &tableName) const;
    std::string generateUpdateQuery(const std::string &tableName, int paramCount) const;

};
}

#endif // MANIPULATOR_H
