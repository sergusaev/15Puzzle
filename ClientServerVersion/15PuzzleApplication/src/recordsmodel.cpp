#include "recordsmodel.h"
#include <QDebug>

RecordsModel::RecordsModel()
{
    connect(&m_recordsHandler, &RequestsHandlerClient::topTimeRequestCompleted,
                this, &RecordsModel::onTopTimeDownloaded);
    connect(&m_recordsHandler, &RequestsHandlerClient::topTurnsRequestCompleted,
            this, &RecordsModel::onTopTurnsDownloaded);
    connect(&m_recordsHandler, &RequestsHandlerClient::recordAdditionCompleted,
            this, &RecordsModel::onRecordAdded);
    connect(&m_recordsHandler, &RequestsHandlerClient::userAdditionCompleted,
            this, &RecordsModel::onUserAdded);
    connect(&m_recordsHandler, &RequestsHandlerClient::passwordRequestCompleted,
            this, &RecordsModel::onPasswordDownloaded);
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
    bool requestResult {m_recordsHandler.requestTopTime(dimension)};
    if (requestResult) {
        qDebug() << "Sending request of records via time succeed!";
    } else {
        qCritical() << "Sending request of records via time failed!";
    }

}

void RecordsModel::getTurnsRanking(int dimension)
{
    bool requestResult {m_recordsHandler.requestTopTurns(dimension)};
    if (requestResult) {
        qDebug() << "Sending request of records via turns succeed!";
    } else {
        qCritical() << "Sending request of records via turns failed!";
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

void RecordsModel::onTopTimeDownloaded(const std::vector<Record> &data)
{
    beginResetModel();
    std::vector<Record> topTimeResult {data};
    m_records.swap(topTimeResult);
    endResetModel();
}

void RecordsModel::onTopTurnsDownloaded(const std::vector<Record> &data)
{
    beginResetModel();
    std::vector<Record> topTurnsResult {data};
    m_records.swap(topTurnsResult);
    endResetModel();
}

void RecordsModel::onRecordAdded()
{

}

void RecordsModel::onUserAdded()
{

}

void RecordsModel::onPasswordDownloaded(const QString &password)
{

}
