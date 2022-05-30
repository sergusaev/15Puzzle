#include "record.h"

Record::Record(const QString &newNickname, const int newTime, const int newTurns, const DBTypes::DBIndex dbID)
            : m_nickname(newNickname)
            , m_time(newTime)
            , m_turns(newTurns)
            , m_dbID(dbID)
{

}

int Record::time() const
{
    return m_time;
}

void Record::setTime(const int newTime)
{
    m_time = newTime;
}

int Record::turns() const
{
    return m_turns;
}

void Record::setTurns(const int newTurns)
{
    m_turns = newTurns;
}

DBTypes::DBIndex Record::dbID() const
{
    return m_dbID;
}

void Record::setDbID(DBTypes::DBIndex newDbID)
{
    m_dbID = newDbID;
}


const QString &Record::nickname() const
{
    return m_nickname;
}

void Record::setNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}
