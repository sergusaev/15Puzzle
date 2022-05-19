#include "recordshandler.h"
#include "processor.h"

RecordsHandler::RecordsHandler()
    : m_processor {new db::Processor{}}
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
                        entry[3].toInt()
        };
    });
    return target;
}

DBTypes::DBIndex RecordsHandler::addRecord(const Record &record)
{
    DBTypes::DBResult result;
    DBTypes::DBIndex index;
    std::tie(result, index) = m_processor->insertDataRecord(DBTypes::DBTables::Records,
                                                            {record.nickname(), record.time(), record.turns(), record.dbID()});
    return (result == DBTypes::DBResult::OK) ? index : -1;
}

bool RecordsHandler::removeRecord(const DBTypes::DBIndex index)
{
    DBTypes::DBResult result;
    result = m_processor->removeDataRecord(DBTypes::DBTables::Records, index);
    return result == DBTypes::DBResult::OK;
}

bool RecordsHandler::updateRecord(const DBTypes::DBIndex index, const Record &updatedRecord)
{
    DBTypes::DBResult result;
    result = m_processor->updateDataRecord(DBTypes::DBTables::Records,
                                           index,
                                           {updatedRecord.nickname(),
                                            updatedRecord.time(),
                                            updatedRecord.turns(),
                                            updatedRecord.dbID()});
#ifdef DEBUG_OUTPUT
    qDebug() << "In function RecordsHandler::updateRecord(<args>) ID of record to update:" << index;
#endif
    return result == DBTypes::DBResult::OK;

}
