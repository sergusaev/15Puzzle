#include "recordsmanager.h"
#include <processorserver.h>
#include <QDebug>

RecordsManager::RecordsManager()
    : m_processor {new db::ProcessorServer{}}
{

}

RecordsManager::~RecordsManager()
{

}



std::vector<QVariant> transform (const std::vector<DBTypes::DBEntry>& source) {
    std::vector<QVariant> target;
    std::transform(source.begin(),
                   source.end(),
                   std::back_inserter(target),
                   [](const DBTypes::DBEntry& entry){return QVariant::fromValue(entry);});


    return target;
}

std::pair<bool, QVariant> RecordsManager::findNickname(const QVariant &nicknameData)
{
    DBTypes::DBResult resultState;
    QVariant returnData;
    std::tie(resultState, returnData) = m_processor->getPasswordData(nicknameData.toString());
    if(returnData.isNull()){
        returnData.clear();
        returnData = QVariant::fromValue(false);
    } else {
        returnData.clear();
        returnData = QVariant::fromValue(true);
    }

    return {resultState == DBTypes::DBResult::OK, returnData};
}

std::pair<bool,QVariant> RecordsManager::getPassword(const QVariant &nicknameData)
{
    DBTypes::DBResult resultState;
    QVariant returnData;
    std::tie(resultState, returnData) = m_processor->getPasswordData(nicknameData.toString());
    return {resultState == DBTypes::DBResult::OK, returnData};

}


std::pair<bool, std::vector<QVariant>> RecordsManager::getTopTime(const QVariant &dimensionData)
{

    DBTypes::DBResult result;
    std::vector<DBTypes::DBEntry> entries;
    std::tie(result, entries) = m_processor->requestTopTimeData(DBTypes::DBTables::Records, dimensionData.toInt());
    return {result == DBTypes::DBResult::OK, transform(entries)};
}

std::pair<bool, std::vector<QVariant>> RecordsManager::getTopTurns(const QVariant &dimensionData)
{
    DBTypes::DBResult result;
    std::vector<DBTypes::DBEntry> entries;
    std::tie(result, entries) = m_processor->requestTopTurnsData(DBTypes::DBTables::Records, dimensionData.toInt());
    return {result == DBTypes::DBResult::OK, transform(entries)};
}

bool RecordsManager::addUser(const DBTypes::DBEntry &entry)
{
    DBTypes::DBResult result = m_processor->insertDataRecord(DBTypes::DBTables::Users, entry);
    return result == DBTypes::DBResult::OK;
}

bool RecordsManager::addRecord(const DBTypes::DBEntry &entry)
{
    DBTypes::DBResult result = m_processor->insertDataRecord(DBTypes::DBTables::Records, entry);
    return result == DBTypes::DBResult::OK;
}

bool RecordsManager::addRecordMultiple(const DBTypes::DBEntry &entry, int paramCount)
{
    DBTypes::DBResult result = m_processor->insertDataRecordMultiple(DBTypes::DBTables::Records, entry, paramCount);
    return result == DBTypes::DBResult::OK;
}


