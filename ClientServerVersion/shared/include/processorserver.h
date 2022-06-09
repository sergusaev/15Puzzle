#ifndef PROCESSORSERVER_H
#define PROCESSORSERVER_H

#include "processor.h"

namespace db {
class ProcessorServer
{
public:
    ProcessorServer();
    ~ProcessorServer();
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTopTimeData(DBTypes::DBTables table, int dimension);
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTopTurnsData(DBTypes::DBTables table, int dimension);
    QVariant getPasswordData(const QString& nickname);
    std::pair<DBTypes::DBResult, DBTypes::DBIndex> insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry& recordData);

private:
    std::unique_ptr<db::Processor> m_d;
};

}


#endif // PROCESSORSERVER_H
