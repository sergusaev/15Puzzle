#include "requestshandlerclient.h"


RequestsHandlerClient::RequestsHandlerClient()
    : m_clientManager {ClientManager::instance()}
{
    connect(&m_clientManager, &ClientManager::connectionStateChanged,
            this, &RequestsHandlerClient::onConnectionStateChanged);
    connect(&m_clientManager, &ClientManager::topTimeResponse,
            this, &RequestsHandlerClient::onTopTimeDownloadSucceed);
    connect(&m_clientManager, &ClientManager::topTurnsResponse,
            this, &RequestsHandlerClient::onTopTurnsDownloadSucceed);
    connect(&m_clientManager, &ClientManager::addRecordResponse,
            this, &RequestsHandlerClient::onRecordAdditionSucceed);
    connect(&m_clientManager, &ClientManager::addUserResponse,
            this, &RequestsHandlerClient::onUserAdditionSucceed);
    connect(&m_clientManager, &ClientManager::passwordResponse,
            this, &RequestsHandlerClient::onPasswordDownloadSucceed);
}

bool RequestsHandlerClient::requestTopTime(int dimension)
{
    QVariant data {QVariant::fromValue(dimension)};
    const net::Package package {data, net::PackageType::TOP_TIME_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool RequestsHandlerClient::requestTopTurns(int dimension)
{
    QVariant data {QVariant::fromValue(dimension)};
    const net::Package package {data, net::PackageType::TOP_TURNS_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool RequestsHandlerClient::requestRecordAddition(const Record &record)
{
    QVariantList dataList {QVariant::fromValue(record.nickname()),
                           QVariant::fromValue(record.time()),
                           QVariant::fromValue(record.turns()),
                           QVariant::fromValue(record.dimension())};
    const net::Package package {QVariant::fromValue(dataList), net::PackageType::ADD_RECORD_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool RequestsHandlerClient::requestUserAddition(const QString &nickname, const QString &password)
{
    QVariantList dataList {QVariant::fromValue(nickname),QVariant::fromValue(password)};
    const net::Package package {QVariant::fromValue(dataList), net::PackageType::ADD_USER_REQUEST};
    return m_clientManager.sendPackage(package);
}

bool RequestsHandlerClient::requestPassword(const QString &nickname)
{
    QVariant data {QVariant::fromValue(nickname)};
    const net::Package package {data, net::PackageType::PASSWORD_REQUEST};
    return m_clientManager.sendPackage(package);
}

void RequestsHandlerClient::onConnectionStateChanged(net::ConnectionState state)
{
//    if (state == net::ConnectionState::Connected)
//    {
//        requestBrowseContacts();
//    }
}

Record transformQVariantListToRecord(QVariantList& dataList) {
    Record record;
    record.setNickname(std::move(dataList.first().toString()));
    dataList.pop_front();
    record.setTime(dataList.first().toInt());
    dataList.pop_front();
    record.setTurns(dataList.first().toInt());
    dataList.pop_front();
    record.setDimension(dataList.first().toInt());
    return record;
}

static std::vector<Record> transform(const std::vector<QVariant>& source)
{
    std::vector<Record> target;
    std::transform(source.begin(),
                   source.end(),
                   std::back_inserter(target),
                   [](const QVariant& entry) {
                                        QVariantList dataList = entry.toList();
                                        Record record  = transformQVariantListToRecord(dataList);
                                        return record;
                                     });
    return target;
}


void RequestsHandlerClient::onTopTimeDownloadSucceed(const std::vector<QVariant> &data)
{
    emit topTimeRequestCompleted(transform(data));
}


void RequestsHandlerClient::onTopTurnsDownloadSucceed(const std::vector<QVariant> &data)
{
    emit topTurnsRequestCompleted(transform(data));
}


void RequestsHandlerClient::onRecordAdditionSucceed()
{
    emit recordAdditionCompleted();
}

void RequestsHandlerClient::onUserAdditionSucceed()
{
    emit userAdditionCompleted();
}

void RequestsHandlerClient::onPasswordDownloadSucceed(const QVariant &data)
{
    emit passwordRequestCompleted(data.toString());
}
