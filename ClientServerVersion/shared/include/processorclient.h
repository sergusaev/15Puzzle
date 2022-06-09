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
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTableData(DBTypes::DBTables table);
    std::pair<DBTypes::DBResult, DBTypes::DBIndex> insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry& recordData);
private:
    std::unique_ptr<db::Processor> m_d;
};

}


#endif // PROCESSORCLIENT_H