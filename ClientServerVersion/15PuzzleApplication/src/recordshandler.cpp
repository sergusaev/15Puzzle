#include "recordshandler.h"
#include "processor.h"

RecordsHandler::RecordsHandler()
    : m_processor {new db::Processor(DBTypes::DBManagerType::CLIENT)}
{

}

RecordsHandler::~RecordsHandler()
{

}


std::vector<Record> transform (const std::vector<DBTypes::DBEntry>& source) {
    std::vector<Record> target;
    std::transform(source.begin(), source.end(), std::back_inserter(target), [](const DBTypes::DBEntry& entry){
        return Record  {entry[0].toString(),
                        entry[1].toInt(),
                        entry[2].toInt(),
        };
    });
    return target;
}

std::pair<bool, std::vector<Record> > RecordsHandler::browseBestInTime(int dimension)
{
    DBTypes::DBResult result;
    std::vector<DBTypes::DBEntry> entries;
    std::tie(result, entries) = m_processor->requestTopTimeData(DBTypes::DBTables::Records, dimension);
    return {result == DBTypes::DBResult::OK, transform(entries)};
}

std::pair<bool, std::vector<Record> > RecordsHandler::browseBestInTurns(int dimension)
{
    DBTypes::DBResult result;
    std::vector<DBTypes::DBEntry> entries;
    std::tie(result, entries) = m_processor->requestTopTurnsData(DBTypes::DBTables::Records, dimension);
    return {result == DBTypes::DBResult::OK, transform(entries)};
}


DBTypes::DBIndex RecordsHandler::addRecord(const Record &record)
{
    DBTypes::DBResult result;
    DBTypes::DBIndex index;
    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::Records,
                                                            {record.nickname(), record.time(), record.turns(), record.dimension()});
    return (result == DBTypes::DBResult::OK) ? index : -1;
}

DBTypes::DBIndex RecordsHandler::addUserLogPass(const QString &nickname, const QString &password)
{
    DBTypes::DBResult result;
    DBTypes::DBIndex index;
    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::Users,
                                                            {nickname, password});
    return (result == DBTypes::DBResult::OK) ? index : -1;
}

QString RecordsHandler::getPassword(const QString &nickname)
{
    QString ret = m_processor->getPasswordData(nickname).toString();
    return ret;
}

