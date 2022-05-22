#ifndef RECORD_H
#define RECORD_H

#include <dbtypes.h>
#include <QString>


class Record
{
public:
    Record() = default;

    Record(const QString& newNickname, const int newTime, const int newTurns, const DBTypes::DBIndex dbID = -1);

    const QString &nickname() const;
    void setNickname(const QString &newNickname);

    int time() const;
    void setTime(const int newTime);

    int turns() const;
    void setTurns(const int newTurns);



    DBTypes::DBIndex dbID() const;
    void setDbID(DBTypes::DBIndex newDbID);

    bool operator==(const Record& other) const{
        return (other.nickname() == nickname()
                && other.time() == time()
                && other.turns() == turns());
    }

private:
    QString m_nickname;
    int m_time;
    int m_turns;
    DBTypes::DBIndex m_dbID;
};

#endif // RECORD_H
