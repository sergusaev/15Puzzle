#ifndef PROCESSOR_H
#define PROCESSOR_H


#include "dbtypes.h"
#include <memory>

namespace db
{
class Processor
{
public:
    Processor();
    ~Processor();
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTableData(DBTypes::DBTables table);
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTopTimeData(DBTypes::DBTables table, int dimension);
    std::pair<DBTypes::DBResult, std::vector<DBTypes::DBEntry>> requestTopTurnsData(DBTypes::DBTables table, int dimension);
    QVariant getPasswordData(const QString& nickname);
    std::pair<DBTypes::DBResult, DBTypes::DBIndex> insertDataRecord(DBTypes::DBTables table, const DBTypes::DBEntry& recordData);


private:
    struct ProcessorPrivate;
    std::unique_ptr<ProcessorPrivate> m_d;
};
}

#endif // PROCESSOR_H
