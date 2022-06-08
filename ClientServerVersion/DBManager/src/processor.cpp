#include "processor.h"
#include "dbmapper.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <sstream>


namespace db
{

//manipulator methods
Processor::Processor(DBTypes::DBManagerType managerType)
{

}

std::pair<DBTypes::DBResult, DBTypes::DBIndex> Processor::insertRow(const std::string& tableName, const DBTypes::DBEntry& recordData)
{
    const std::string& query {Processor::generateInsertQuery(tableName, recordData.size())};
    const std::pair<DBTypes::DBResult, QSqlQuery>& result {m_executor.execute(query, recordData)};
    return std::make_pair(result.first, result.second.lastInsertId().toInt());
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
            for (int i = 0; i < resultRecord.count(); ++i)
            {
                resultList.push_back(resultRecord.value(i));
            }
            returnData.push_back(std::move(resultList));
        }
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
    std::string query = "SELECT * FROM "
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
    std::string query = "SELECT * FROM "
            + tableName
            + " WHERE "
            + tablesMapping.at(tableName)[3]
            + " = ?"
            + " ORDER BY "
            + tablesMapping.at(tableName)[1]
            + " ASC LIMIT 10";
    return query;
}


}
//namespace db
//{
//struct Processor::ProcessorPrivate
//{
//    Selector selector;
//    Manipulator manipulator;
//};

//db::Processor::Processor()
//    : m_d {new ProcessorPrivate {}}
//{

//}

//Processor::~Processor()
//{
//}

//std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> Processor::requestTableData(DBTypes::DBTables table)
//{
//    std::vector<QVariantList> result;
//    const DBTypes::DBResult resultState {m_d->selector.selectAll(tableMapper.at(table), result)};
//    return std::make_pair(resultState, std::move(result));
//}

//std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry> > Processor::requestTopTimeData(DBTypes::DBTables table, int dimension)
//{
//    std::vector<QVariantList> result;
//    const DBTypes::DBResult resultState {m_d->selector.selectTopTime(tableMapper.at(table), dimension, result)};
//    return std::make_pair(resultState, std::move(result));
//}

//std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry> > Processor::requestTopTurnsData(DBTypes::DBTables table, int dimension)
//{
//    std::vector<QVariantList> result;
//    const DBTypes::DBResult resultState {m_d->selector.selectTopTurns(tableMapper.at(table), dimension, result)};
//    return std::make_pair(resultState, std::move(result));
//}

//QVariant Processor::getPasswordData(const QString &nickname)
//{
//    QVariant returnData;
//    m_d->selector.selectUserPassword(nickname.toStdString(), returnData);
//    return returnData;
//}

//std::pair<DBTypes::DBResult, DBTypes::DBIndex> Processor::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
//{
//    return m_d->manipulator.insertRow(tableMapper.at(table), recordData);
//}



//}
