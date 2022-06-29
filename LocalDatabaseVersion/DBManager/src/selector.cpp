#include "selector.h"
#include "dbmapper.h"
#include "executor.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <vector>

using namespace DBTypes;

namespace db
{
DBResult Selector::selectAll(const std::string& tableName, std::vector<QVariantList>& returnData)
{
    const std::string query {generateSelectAllQuery(tableName)};
    DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query);

    if (result == DBResult::OK)
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

DBResult Selector::selectTopTime(const std::string &tableName, int dimension, std::vector<QVariantList> &returnData)
{
    const std::string query {generateSelectTopTimeQuery(tableName)};
    DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query, {dimension});
    if (result == DBResult::OK)
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
DBResult Selector::selectTopTurns(const std::string &tableName, int dimension, std::vector<QVariantList> &returnData)
{
    const std::string query {generateSelectTopTurnsQuery(tableName)};
    DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query, {dimension});
    if (result == DBResult::OK)
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

DBResult Selector::selectUserPassword(const std::string &username, QVariant &returnData)
{
    const std::string query {"SELECT Password FROM Users WHERE Nickname = \""  + username + "\""};
    DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_executor.execute(query);
    if (result == DBResult::OK)
    {
        resultQuery.first();
        const QSqlRecord& resultRecord = resultQuery.record();
        returnData = resultRecord.value(0);
    }
    return result;
}


std::string Selector::generateSelectAllQuery(const std::string& tableName) const
{
    std::string query = "SELECT rowid, * FROM " + tableName;
    return query;
}

std::string Selector::generateSelectTopTimeQuery(const std::string &tableName) const
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

std::string Selector::generateSelectTopTurnsQuery(const std::string &tableName) const
{
    std::string query = "SELECT * FROM "
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
