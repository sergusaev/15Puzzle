#ifndef PROCESSORCLIENT_H
#define PROCESSORCLIENT_H

#include "dbtypes.h"
#include "processor.h"

namespace db {

class ProcessorClient
{
public:
    ProcessorClient();
    ~ProcessorClient();
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestCacheData(DBTypes::DBTables table);
    std::pair<DBTypes::DBResult, DBTypes::DBEntry> requestFirstRecordData(DBTypes::DBTables table);
    DBTypes::DBResult deleteFirstRecord(DBTypes::DBTables table);
    DBTypes::DBResult deleteCacheData(DBTypes::DBTables table);
    DBTypes::DBResult insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry& recordData);
private:
    std::unique_ptr<db::Processor> m_d;
};

}


#endif // PROCESSORCLIENT_H
