#ifndef RECORDSHANDLER_H
#define RECORDSHANDLER_H

#include <vector>
#include <memory>
#include "record.h"


namespace db {
class Processor;
}

class RecordsHandler
{
public:
    RecordsHandler();
    ~RecordsHandler();
    std::pair<bool, std::vector<Record>> browseBestInTime();
    std::pair<bool, std::vector<Record>> browseBestInTurns();
    DBTypes::DBIndex addRecord (const Record& record);
//    bool removeRecord (const DBTypes::DBIndex index);
//    bool updateRecord (const DBTypes::DBIndex index, const Record& updatedRecord);

private:
    std::unique_ptr<db::Processor> m_processor;
};

#endif // RECORDSHANDLER_H
