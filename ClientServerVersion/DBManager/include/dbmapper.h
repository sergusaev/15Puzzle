#ifndef DBMAPPER_H
#define DBMAPPER_H

#include "dbtypes.h"

namespace db
{
static const std::map<DBTypes::DBTables, std::string> tableMapper {
    {DBTypes::DBTables::Records, "Records"},
    {DBTypes::DBTables::Users, "Users"},
    {DBTypes::DBTables::RecordsCache, "RecordsCache"}
};

static const std::map<std::string, std::vector<std::string>> tablesMapping = {
    {"Records", {"Nickname", "Time", "Turns", "Dimension"}},
    {"Users", {"Nickname", "Password"}},
    {"RecordsCache", {"Nickname", "Time", "Turns", "Dimension"}}
};
}


#endif // DBMAPPER_H
