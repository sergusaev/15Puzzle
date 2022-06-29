#include "processorclient.h"
#include "dbmapper.h"

namespace db
{

ProcessorClient::ProcessorClient()
    : m_d {new Processor(DBTypes::DBManagerType::CLIENT)}
{

}

ProcessorClient::~ProcessorClient()
{
}

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry> > ProcessorClient::requestCacheData(DBTypes::DBTables table)
{
    std::vector<DBTypes::DBEntry> result;
    DBTypes::DBResult resultState;
    std::tie(resultState, result) = m_d->requestTableData(table);
    return {resultState, result};
}

std::pair<DBTypes::DBResult, DBTypes::DBEntry> ProcessorClient::requestFirstRecordData(DBTypes::DBTables table)
{
    QVariantList result;
    const DBTypes::DBResult resultState {m_d->selectFirst(tableMapper.at(table), result)};
    return std::make_pair(resultState, std::move(result));
}

DBTypes::DBResult ProcessorClient::deleteFirstRecord(DBTypes::DBTables table)
{
    return m_d->deleteFirst(tableMapper.at(table));
}

DBTypes::DBResult ProcessorClient::deleteCacheData(DBTypes::DBTables table)
{
    return m_d->deleteAll(tableMapper.at(table));
}


DBTypes::DBResult ProcessorClient::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
{
    return m_d->insertRow(tableMapper.at(table), recordData);
}



}
