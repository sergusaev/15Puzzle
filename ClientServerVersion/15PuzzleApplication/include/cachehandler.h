#ifndef CACHEHANDLER_H
#define CACHEHANDLER_H

#include <vector>
#include <memory>
#include "record.h"


namespace db {
class ProcessorClient;
}

class CacheHandler
{
public:
    CacheHandler();
    ~CacheHandler();
    DBTypes::DBIndex addRecord (const Record& record);   
    std::pair<bool, Record> browseFirstCacheRecord();
    bool deleteFirstCacheRecord();

//    DBTypes::DBIndex addUserLogPass (const QString& nickname, const QString& password);
//    QString getPassword(const QString& nickname);

private:
    std::unique_ptr<db::ProcessorClient> m_processor;
};

#endif // CACHEHANDLER_H
