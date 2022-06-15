#ifndef RECORD_H
#define RECORD_H

#include <dbtypes.h>
#include <QString>


class Record
{
public:
    Record() = default;

    Record(const QString& newNickname, const int newTime, const int newTurns,  const int newDimension = - 1);

    const QString &nickname() const;
    void setNickname(const QString &newNickname);

    int time() const;
    void setTime(const int newTime);

    int turns() const;
    void setTurns(const int newTurns);

    int dimension() const;
    void setDimension(int newDimension);

    bool operator==(const Record& other) const{
        return (other.nickname() == nickname()
                && other.time() == time()
                && other.turns() == turns()
                && other.dimension() == m_dimension);
    }


private:
    QString m_nickname;
    int m_time;
    int m_turns;
    int m_dimension;
};

#endif // RECORD_H
