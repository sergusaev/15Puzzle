#ifndef SELECTOR_H
#define SELECTOR_H


#include <QVariantList>
#include "dbtypes.h"
#include "executor.h"

namespace db
{
class Selector
{
public:
    DBTypes::DBResult selectAll(const std::string& tableName,
                                std::vector<QVariantList>& returnData);
    DBTypes::DBResult selectTopTime(const std::string& tableName,
                                std::vector<QVariantList>& returnData);
    DBTypes::DBResult selectTopTurns(const std::string& tableName,
                                    std::vector<QVariantList>& returnData);

private:
    Executor m_executor;
    std::string generateSelectAllQuery(const std::string& tableName) const;
    std::string generateSelectTopTimeQuery(const std::string& tableName) const;
    std::string generateSelectTopTurnsQuery(const std::string& tableName) const;
};
}

#endif // SELECTOR_H
