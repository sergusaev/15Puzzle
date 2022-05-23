#include "recordsmodel.h"
#include <QDebug>

RecordsModel::RecordsModel()
{
//    connect();
}

QHash<int, QByteArray> RecordsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[RecordRoles::NicknameRole] = "nickname";
    roles[RecordRoles::TimeRole] = "time";
    roles[RecordRoles::TurnsRole] = "turns";
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
    default:
    {
        return true;
    }
    }
}


void RecordsModel::getTimeRanking()
{
    bool requestResult {false};
    std::vector<Record> recordsResult;
    std::tie(requestResult, recordsResult) = m_recordsHandler.browseBestInTime();
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

void RecordsModel::getTurnsRanking()
{
    bool requestResult {false};
    std::vector<Record> recordsResult;
    std::tie(requestResult, recordsResult) = m_recordsHandler.browseBestInTurns();
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
    return  QString("%1 : %2").arg(time / 60).arg(time % 60);
}
