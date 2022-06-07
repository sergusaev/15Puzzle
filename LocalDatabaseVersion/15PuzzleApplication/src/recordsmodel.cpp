#include "recordsmodel.h"
#include <QDebug>

RecordsModel::RecordsModel()
{
}

QHash<int, QByteArray> RecordsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RecordRoles::NicknameRole] = "nickname";
    roles[RecordRoles::TimeRole] = "time";
    roles[RecordRoles::TurnsRole] = "turns";
    roles[RecordRoles::DimensionRole] = "dimension";
    return roles;
}

int RecordsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_records.size());
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index)) {
        return {};
    }
    const Record& record {m_records.at(index.row())};
    switch (role) {
    case RecordRoles::NicknameRole: {
        return QVariant::fromValue(record.nickname());
    }
    case RecordRoles::TimeRole: {
        return QVariant::fromValue(timeToString(record.time()));
    }
    case RecordRoles::TurnsRole: {
        return QVariant::fromValue(record.turns());
    }
    case RecordRoles::DimensionRole: {
        return QVariant::fromValue(record.dimension());
    }
    default:
    {
        return true;
    }
    }
}


void RecordsModel::getTimeRanking(int dimension)
{
    bool requestResult {false};
    std::vector<Record> recordsResult;
    std::tie(requestResult, recordsResult) = m_recordsHandler.browseBestInTime(dimension);
    if (requestResult) {
        beginResetModel();
        m_records.swap(recordsResult);
        endResetModel();
    } else {
        qCritical() << "Browsing records via time failed!";
    }
    for(const auto& record : m_records) {
        qDebug() <<  "Database ID: " << record.dbID() << " "
                 <<  "Nickname: " << record.nickname() << " "
                 <<  "Time: " << record.time() << " "
                 <<  "Turns: " << record.turns() << "\n";
    }

}

void RecordsModel::getTurnsRanking(int dimension)
{
    bool requestResult {false};
    std::vector<Record> recordsResult;
    std::tie(requestResult, recordsResult) = m_recordsHandler.browseBestInTurns(dimension);
    if (requestResult) {
        beginResetModel();
        m_records.swap(recordsResult);
        endResetModel();
    } else {
        qCritical() << "Browsing records via turns failed!";
    }
    for(const auto& record : m_records) {
        qDebug() <<  "Database ID: " << record.dbID() << " "
                 <<  "Nickname: " << record.nickname() << " "
                 <<  "Time: " << record.time() << " "
                 <<  "Turns: " << record.turns() << "\n";
    }
}

QString RecordsModel::timeToString(int time) const
{
    QString min = ((time / 60) < 10) ? QString("0%1").arg(time / 60) : QString("%1").arg(time / 60);
    QString sec = ((time % 60) < 10) ? QString("0%1").arg(time % 60) : QString("%1").arg(time % 60);

    return min + ":" + sec;
}

QString RecordsModel::rankToString(int rank) const
{
    return QString("%1.").arg(rank);
}
