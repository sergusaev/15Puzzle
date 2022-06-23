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
    ~CacheHandler();
    static CacheHandler *instance();
    bool addRecord(const Record& record);
    std::pair<bool, DBTypes::DBEntry> browseFirstCacheRecord();
    bool deleteFirstCacheRecord();
private:
    CacheHandler();
    std::unique_ptr<db::ProcessorClient> m_processor;
};

#endif // CACHEHANDLER_H
