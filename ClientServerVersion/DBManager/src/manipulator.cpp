#include <manipulator.h>
#include <sstream>
#include "dbmapper.h"

using namespace DBTypes;

namespace db
{

std::pair<DBResult, DBIndex> Manipulator::insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData)
{
    const std::string& query {generateInsertQuery(tableName, recordData.size())};
    const std::pair<DBResult, QSqlQuery>& result {m_executor.execute(query, recordData)};
    return std::make_pair(result.first, result.second.lastInsertId().toInt());
}

std::string Manipulator::generateBindString(int paramCount) const
{
    std::ostringstream bindings;
    std::fill_n(std::ostream_iterator<std::string>(bindings),
                paramCount,
                "?,");
    std::string bindString = bindings.str();
    bindString.pop_back(); // the last ","
    return bindString;
}

std::string Manipulator::generateInsertQuery(const std::string& tableName, int paramCount) const
{
    std::string tableColumns = tablesMapping.at(tableName)[0] + ",";
    for(int i = 1; i < paramCount; ++i) {
        tableColumns += " " + tablesMapping.at(tableName)[i] + ",";
    }
    tableColumns.pop_back(); //the last ","
    std::string query = "INSERT INTO " + tableName +  " (" + tableColumns + ")" +
                        " VALUES (";

    query += generateBindString(paramCount);
    query += ")";
    return query;
}


}
