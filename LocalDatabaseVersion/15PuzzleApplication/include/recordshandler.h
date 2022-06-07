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
    std::pair<bool, std::vector<Record>> browseBestInTime(int dimension);
    std::pair<bool, std::vector<Record>> browseBestInTurns(int dimension);
    DBTypes::DBIndex addRecord (const Record& record);
    DBTypes::DBIndex addUserLogPass (const QString& nickname, const QString& password);
    QString getPassword(const QString& nickname);


private:
    std::unique_ptr<db::Processor> m_processor;
};

#endif // RECORDSHANDLER_H
