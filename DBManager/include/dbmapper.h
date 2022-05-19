#ifndef DBMAPPER_H
#define DBMAPPER_H

#include "dbtypes.h"

namespace db
{
static const std::map<DBTypes::DBTables, std::string> tableMapper {
    {DBTypes::DBTables::Records, "Records"}
};

static const std::map<std::string, std::vector<std::string>> tablesMapping = {
    {"Records", {"Nickname", "Time", "Turns"}}
};
}


#endif // DBMAPPER_H
