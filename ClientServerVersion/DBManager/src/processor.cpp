#include "processor.h"
#include "dbmapper.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <sstream>


namespace db
{

Processor::Processor(DBTypes::DBManagerType managerType)
    : m_executor(managerType)
{
}


//manipulator methods

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> Processor::requestTableData(DBTypes::DBTables table)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {selectAll(tableMapper.at(table), result)};
    return std::make_pair(resultState, std::move(result));
}

DBTypes::DBResult Processor::insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData)
{
    const std::string& query {Processor::generateInsertQuery(tableName, recordData.size())};
    const std::pair<DBTypes::DBResult, QSqlQuery>& result {m_executor.execute(query, recordData)};
    return result.first;
}

DBTypes::DBResult Processor::insertRowMultiple(const std::string &tableName, const DBTypes::DBEntry &recordData, int paramCount)
{

    int multiplier = recordData.size() / paramCount;
    const std::string& query {Processor::generateMultipleInsertQuery(tableName, paramCount, multiplier)};
    const std::pair<DBTypes::DBResult, QSqlQuery>& result {m_executor.execute(query, recordData)};
    return result.first;
}



DBTypes::DBResult Processor::deleteFirst(const std::string &tableName)
{
    const std::string& query {"DELETE FROM " + tableName + " WHERE rowid = 1"};
    const std::pair<DBTypes::DBResult, QSqlQuery>& result {m_executor.execute(query)};
    return result.first;
}

DBTypes::DBResult Processor::deleteAll(const std::string &tableName)
{
    const std::string& query {"DELETE FROM " + tableName};
    const std::pair<DBTypes::DBResult, QSqlQuery>& result {m_executor.execute(query)};
    return result.first;
}




std::string Processor::generateBindString(int paramCount) const
{
    std::ostringstream bindings;
    std::fill_n(std::ostream_iterator<std::string>(bindings),
                paramCount,
                "?,");
    std::string bindString = bindings.str();
    bindString.pop_back(); // the last ","
    return bindString;
}

std::string Processor::generateInsertQuery(const std::string& tableName, int paramCount) const
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

std::string Processor::generateMultipleInsertQuery(const std::string &tableName, int paramCount, int multiplier) const
{
    std::string tableColumns = tablesMapping.at(tableName)[0] + ",";
    for(int i = 1; i < paramCount; ++i) {
        tableColumns += " " + tablesMapping.at(tableName)[i] + ",";
    }
    tableColumns.pop_back(); //the last ","
    std::string query = "INSERT INTO " + tableName +  " (" + tableColumns + ")" +
                        " VALUES ";
    for(int i = 0; i < multiplier; ++i) {
        query += "(";
        query += generateBindString(paramCount);
        query += "),";
    }
    query.pop_back(); //the last ","
    return query;
}



//selector methods


DBTypes::DBResult Processor::selectAll(const std::string& tableName, std::vector<QVariantList>& returnData)
{
    const std::string query {Processor::generateSelectAllQuery(tableName)};
    DBTypes::DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query);
    if (result == DBTypes::DBResult::OK)
    {
        while (resultQuery.next())
        {
            const QSqlRecord& resultRecord = resultQuery.record();
            QVariantList resultList;
            for (int i = 1; i < resultRecord.count(); ++i)
            {
                resultList.push_back(resultRecord.value(i));
            }
            returnData.push_back(std::move(resultList));
        }
    }
    return result;
}

DBTypes::DBResult Processor::selectFirst(const std::string &tableName, QVariantList &returnData)
{
    const std::string query {"SELECT * FROM " + tableName +  " WHERE rowid = 1"};
    DBTypes::DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query);
    if (result == DBTypes::DBResult::OK) {
        resultQuery.first();
        const QSqlRecord& resultRecord = resultQuery.record();
        QVariantList resultList;
        for (int i = 0; i < resultRecord.count(); ++i)
        {
            resultList.push_back(resultRecord.value(i));
        }
        returnData.push_back(std::move(resultList));
    }
    return result;

}

DBTypes::DBResult Processor::selectTopTime(const std::string &tableName, int dimension, std::vector<QVariantList> &returnData)
{
    const std::string query {Processor::generateSelectTopTimeQuery(tableName)};
    DBTypes::DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query, {dimension});
    if (result == DBTypes::DBResult::OK)
    {
        while (resultQuery.next())
        {
            const QSqlRecord& resultRecord = resultQuery.record();
            QVariantList resultList;
            for (int i = 0; i < resultRecord.count(); ++i)
            {
                resultList.push_back(resultRecord.value(i));
            }
            returnData.push_back(std::move(resultList));
        }

    }
    return result;
}

DBTypes::DBResult Processor::selectTopTurns(const std::string &tableName, int dimension, std::vector<QVariantList> &returnData)
{
    const std::string query {Processor::generateSelectTopTurnsQuery(tableName)};
    DBTypes::DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query, {dimension});
    if (result == DBTypes::DBResult::OK)
    {

        while (resultQuery.next())
        {
            const QSqlRecord& resultRecord = resultQuery.record();
            QVariantList resultList;
            for (int i = 0; i < resultRecord.count(); ++i)
            {
                resultList.push_back(resultRecord.value(i));
            }
            returnData.push_back(std::move(resultList));
        }

    }
    return result;
}

DBTypes::DBResult Processor::selectUserPassword(const std::string &username, QVariant &returnData)
{
    const std::string query {"SELECT Password FROM Users WHERE Nickname = \""  + username + "\""};
    DBTypes::DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query);
    if (result == DBTypes::DBResult::OK)
    {
        resultQuery.first();
        const QSqlRecord& resultRecord = resultQuery.record();
        returnData = resultRecord.value(0);
    }
    return result;
}


std::string Processor::generateSelectAllQuery(const std::string& tableName) const
{
    std::string query = "SELECT rowid, * FROM " + tableName;
    return query;
}

std::string Processor::generateSelectTopTimeQuery(const std::string &tableName) const
{
    std::string query = "SELECT DISTINCT "
            + tablesMapping.at(tableName)[0]
            + ", "
            + tablesMapping.at(tableName)[1]
            + " FROM "
            + tableName
            + " WHERE "
            + tablesMapping.at(tableName)[3]
            + " = ?"
            + " ORDER BY "
            + tablesMapping.at(tableName)[1]
            + " ASC LIMIT 10";
    return query;
}

std::string Processor::generateSelectTopTurnsQuery(const std::string &tableName) const
{
    std::string query = "SELECT DISTINCT "
            + tablesMapping.at(tableName)[0]
            + ", "
            + tablesMapping.at(tableName)[2]
            + " FROM "
            + tableName
            + " WHERE "
            + tablesMapping.at(tableName)[3]
            + " = ?"
            + " ORDER BY "
            + tablesMapping.at(tableName)[2]
            + " ASC LIMIT 10";
    return query;
}


}
