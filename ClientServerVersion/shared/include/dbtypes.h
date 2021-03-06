#ifndef DBTYPES_H
#define DBTYPES_H
#include <QVariantList>

namespace DBTypes
{
enum class DBResult {
    OK,
    FAIL
};

enum class DBTables {
    Records = 1,
    Users,
    RecordsCache,
    UsersCahe
};

enum class DBState {
    OK,
    ERROR_NO_DRIVER,
    ERROR_WORKSPACE,
    ERROR_TABLES,
    ERROR_OPENING
};

enum class DBManagerType {
    CLIENT,
    SERVER
};

using DBEntry = QVariantList;
using DBIndex = int;
}
#endif // DBTYPES_H
