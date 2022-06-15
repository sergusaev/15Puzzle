#include "cachehandler.h"
#include "processorclient.h"

CacheHandler::CacheHandler()
    : m_processor {new db::ProcessorClient()}
{

}

CacheHandler::~CacheHandler()
{

}

CacheHandler *CacheHandler::instance()
{
    static CacheHandler *instance = new CacheHandler;
    return instance;
}


std::pair<bool, DBTypes::DBEntry> CacheHandler::browseFirstCacheRecord()
{
    DBTypes::DBResult result;
    DBTypes::DBEntry dataList;
    std::tie(result, dataList) = m_processor->requestFirstRecordData(DBTypes::DBTables::RecordsCache);
    return {result == DBTypes::DBResult::OK, dataList};
}

bool CacheHandler::deleteFirstCacheRecord()
{
    return m_processor->deleteFirstRecord(DBTypes::DBTables::RecordsCache) == DBTypes::DBResult::OK;

}


bool CacheHandler::addRecord(const Record &record)
{
    DBTypes::DBResult result = m_processor->insertDataRecord(DBTypes::DBTables::RecordsCache,
                                                            {record.nickname(), record.time(), record.turns(), record.dimension()});
    return (result == DBTypes::DBResult::OK);
}

bool CacheHandler::addUser(const QString &nickname, const QString &password)
{
    DBTypes::DBResult result = m_processor->insertDataRecord(DBTypes::DBTables::Users, {nickname, password});
    return (result == DBTypes::DBResult::OK);
}


