#include "cachehandler.h"
#include "processorclient.h"

CacheHandler::CacheHandler()
    : m_processor {new db::ProcessorClient()}
{

}

CacheHandler::~CacheHandler()
{

}


//std::vector<Record> transform (const std::vector<DBTypes::DBEntry>& source) {
//    std::vector<Record> target;
//    std::transform(source.begin(), source.end(), std::back_inserter(target), [](const DBTypes::DBEntry& entry){
//        return Record  {entry[0].toString(),
//                        entry[1].toInt(),
//                        entry[2].toInt(),
//                        entry[3].toInt()
//        };
//    });
//    return target;
//}

std::pair<bool, Record> CacheHandler::browseFirstCacheRecord()
{
    DBTypes::DBResult result;
    Record record;
    std::tie(result, record) = m_processor->requestFirstRecordData(DBTypes::DBTables::RecordsCache);
    return {result == DBTypes::DBResult::OK, record};
}

bool CacheHandler::deleteFirstCacheRecord()
{
    return m_processor->deleteFirstRecord(DBTypes::DBTables::RecordsCache) == DBTypes::DBResult::OK;

}

//std::pair<bool, std::vector<Record> > CacheHandler::browseBestInTime(int dimension)
//{
//    DBTypes::DBResult result;
//    std::vector<DBTypes::DBEntry> entries;
//    std::tie(result, entries) = m_processor->requestTopTimeData(DBTypes::DBTables::Records, dimension);
//    return {result == DBTypes::DBResult::OK, transform(entries)};
//}

//std::pair<bool, std::vector<Record> > CacheHandler::browseBestInTurns(int dimension)
//{
//    DBTypes::DBResult result;
//    std::vector<DBTypes::DBEntry> entries;
//    std::tie(result, entries) = m_processor->requestTopTurnsData(DBTypes::DBTables::Records, dimension);
//    return {result == DBTypes::DBResult::OK, transform(entries)};
//}


DBTypes::DBIndex CacheHandler::addRecord(const Record &record)
{
    DBTypes::DBResult result;
    DBTypes::DBIndex index;
    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::RecordsCache,
                                                            {record.nickname(), record.time(), record.turns(), record.dimension()});
    return (result == DBTypes::DBResult::OK) ? index : -1;
}

//DBTypes::DBIndex CacheHandler::addUserLogPass(const QString &nickname, const QString &password)
//{
//    DBTypes::DBResult result;
//    DBTypes::DBIndex index;
//    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::Users,
//                                                            {nickname, password});
//    return (result == DBTypes::DBResult::OK) ? index : -1;
//}

//QString CacheHandler::getPassword(const QString &nickname)
//{
//    QString ret = m_processor->getPasswordData(nickname).toString();
//    return ret;
//}

