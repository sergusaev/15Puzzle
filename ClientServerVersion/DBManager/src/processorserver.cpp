#include "processorserver.h"
#include "dbmapper.h"

namespace db
{

ProcessorServer::ProcessorServer()
    : m_d {new Processor(DBTypes::DBManagerType::SERVER)}
{

}

ProcessorServer::~ProcessorServer()
{
}


std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry> > ProcessorServer::requestTopTimeData(DBTypes::DBTables table, int dimension)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {m_d->selectTopTime(tableMapper.at(table), dimension, result)};
    return std::make_pair(resultState, std::move(result));
}

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry> > ProcessorServer::requestTopTurnsData(DBTypes::DBTables table, int dimension)
{
    std::vector<QVariantList> result;
    const DBTypes::DBResult resultState {m_d->selectTopTurns(tableMapper.at(table), dimension, result)};
    return std::make_pair(resultState, std::move(result));
}

QVariant ProcessorServer::getPasswordData(const QString &nickname)
{
    QVariant returnData;
    m_d->selectUserPassword(nickname.toStdString(), returnData);
    return returnData;
}

std::pair<DBTypes::DBResult, DBTypes::DBIndex> ProcessorServer::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
{
    return m_d->insertRow(tableMapper.at(table), recordData);
}



}
