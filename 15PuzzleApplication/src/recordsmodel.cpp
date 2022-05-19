#include "recordsmodel.h"

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
