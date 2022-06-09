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

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> ProcessorClient::requestTableData(DBTypes::DBTables table)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {m_d->selectAll(tableMapper.at(table), result)};
    return std::make_pair(resultState, std::move(result));
}


std::pair<DBTypes::DBResult, DBTypes::DBIndex> ProcessorClient::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
{
    return m_d->insertRow(tableMapper.at(table), recordData);
}



}
