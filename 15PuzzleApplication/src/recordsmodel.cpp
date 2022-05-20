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
        return QVariant::fromValue(record.time());
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

void RecordsModel::addRecord(Record record)
{
    DBTypes::DBIndex index = m_recordsHandler.addRecord(record);
    if(index == -1) {
        qDebug() << "Failed to insert new contact into database" << "\n";
        return;
    }
    qDebug() << "New contact has index " << index << " in database" << "\n";
    record.setDbID(index);
    beginInsertRows(QModelIndex(),rowCount(), rowCount());
    m_records.push_back(record);
    for(const auto& record : m_records) {
        qDebug() <<  "Database ID: " << record.dbID() << " "
                 <<  "Nickname: " << record.nickname() << " "
                 <<  "Time: " << record.time() << " "
                 <<  "Turns: " << record.turns() << "\n";
    }
    endInsertRows();
}

void RecordsModel::showTimeTop()
{
    bool requestResult {false};
    std::vector<Record> recordsResult;
    std::tie(requestResult, recordsResult) = m_recordsHandler.browseBestInTime();
    if (requestResult) {
        m_records.swap(recordsResult);
        emit dataChanged(createIndex(0,0), createIndex(m_records.size(), 0));
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

void RecordsModel::showTurnsTop()
{
    bool requestResult {false};
    std::vector<Record> recordsResult;
    std::tie(requestResult, recordsResult) = m_recordsHandler.browseBestInTurns();
    if (requestResult) {
        m_records.swap(recordsResult);
        emit dataChanged(createIndex(0,0), createIndex(m_records.size(), 0));
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
