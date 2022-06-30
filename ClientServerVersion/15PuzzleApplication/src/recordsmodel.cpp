#include "recordsmodel.h"
#include <QDebug>

RecordsModel::RecordsModel()
{
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::topTimeRequestCompleted,
                this, &RecordsModel::onTopTimeDownloaded);
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::topTurnsRequestCompleted,
            this, &RecordsModel::onTopTurnsDownloaded);
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
    return static_cast<int>(m_recordRows.size());
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index)) {
        return {};
    }
    const Row& row {m_recordRows.at(index.row())};
    switch (role) {
    case RecordRoles::NicknameRole: {
        return QVariant::fromValue(row.first);
    }
    case RecordRoles::TimeRole: {
        return QVariant::fromValue(timeToString(row.second));
    }
    case RecordRoles::TurnsRole: {
        return QVariant::fromValue(row.second);
    }

    default:
    {
        return true;
    }
    }
}


void RecordsModel::getTimeRanking(int dimension)
{
    bool requestResult {RequestsHandlerClient::instance()->requestTopTime(dimension)};
    if (requestResult) {
        qDebug() << "Sending request of records via time succeed!";
    } else {
        qCritical() << "Sending request of records via time failed!";
    }

}

void RecordsModel::getTurnsRanking(int dimension)
{
    bool requestResult {RequestsHandlerClient::instance()->requestTopTurns(dimension)};
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

void RecordsModel::onTopTimeDownloaded(const std::vector<Row> &data)
{
    beginResetModel();
    std::vector<Row> topTimeResult {data};
    m_recordRows.swap(topTimeResult);
    endResetModel();
}

void RecordsModel::onTopTurnsDownloaded(const std::vector<Row> &data)
{
    beginResetModel();
    std::vector<Row> topTurnsResult {data};
    m_recordRows.swap(topTurnsResult);
    endResetModel();
}


