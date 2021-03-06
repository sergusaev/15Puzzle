#ifndef CONTACTSREADER_H
#define CONTACTSREADER_H

#include <dbtypes.h>
#include <vector>
#include <memory>
#include <QVariant>

namespace db {
class ProcessorServer;
}

class RecordsManager
{
public:
    RecordsManager();
    ~RecordsManager();

    std::pair<bool,QVariant> findNickname(const QVariant &nicknameData);
    std::pair<bool,QVariant> checkPasswordValidity(const QVariant &data);
    bool addUser (const DBTypes::DBEntry& entry);
    bool addRecord (const DBTypes::DBEntry& entry);
    bool addRecordMultiple (const DBTypes::DBEntry& entry, int paramCount);
    std::pair<bool, std::vector<QVariant> > getTopTime(const QVariant &dimensionData);
    std::pair<bool, std::vector<QVariant> > getTopTurns(const QVariant &dimensionData);

private:
    std::unique_ptr<db::ProcessorServer> m_processor;
};

#endif // CONTACTSREADER_H
