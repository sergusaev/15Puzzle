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
    std::vector<DBTypes::DBEntry> result;
    const DBTypes::DBResult resultState {m_d->selectTopTime(tableMapper.at(table), dimension, result)};
    return std::make_pair(resultState, std::move(result));
}

std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry> > ProcessorServer::requestTopTurnsData(DBTypes::DBTables table, int dimension)
{
    std::vector<DBTypes::DBEntry> result;
    const DBTypes::DBResult resultState {m_d->selectTopTurns(tableMapper.at(table), dimension, result)};
    return std::make_pair(resultState, std::move(result));
}

std::pair<DBTypes::DBResult,QVariant> ProcessorServer::checkPassword(const QVariantList &userData)
{
    QVariant returnData;
    DBTypes::DBResult resultState {m_d->selectUserPassword(userData.front().toString().toStdString(), returnData)};
    qDebug() << "User data password hash: " << userData.back();
    qDebug() << "User ethalon password hash: " << returnData;
    return std::make_pair(resultState, QVariant::fromValue(returnData == userData.back()));
}

std::pair<DBTypes::DBResult, QVariant> ProcessorServer::checkNicknameExistance(const QVariant &nicknameData)
{
    QVariant returnData;
    DBTypes::DBResult resultState {m_d->selectUserPassword(nicknameData.toString().toStdString(), returnData)};
    qDebug() << "User nickname: " << nicknameData;
    qDebug() << "User ethalon password hash: " << returnData;
    return std::make_pair(resultState, QVariant::fromValue(returnData.isNull()));
}



DBTypes::DBResult ProcessorServer::insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry &recordData)
{
    return m_d->insertRow(tableMapper.at(table), recordData);
}

DBTypes::DBResult ProcessorServer::insertDataRecordMultiple(DBTypes::DBTables table, const DBTypes::DBEntry &recordData, int paramCount)
{
    return m_d->insertRowMultiple(tableMapper.at(table), recordData, paramCount);
}



}
