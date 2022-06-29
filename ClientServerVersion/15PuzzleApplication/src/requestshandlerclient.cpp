#include "requestshandlerclient.h"
#include "cachehandler.h"


RequestsHandlerClient::RequestsHandlerClient()
{
    connect(ClientManager::instance(), &ClientManager::connectionStateChanged,
            this, &RequestsHandlerClient::onConnectionStateChanged);
    connect(ClientManager::instance(), &ClientManager::topTimeResponse,
            this, &RequestsHandlerClient::onTopTimeDownloadSucceed);
    connect(ClientManager::instance(), &ClientManager::topTurnsResponse,
            this, &RequestsHandlerClient::onTopTurnsDownloadSucceed);
    connect(ClientManager::instance(), &ClientManager::addRecordResponse,
            this, &RequestsHandlerClient::onRecordAdditionSucceed);
    connect(ClientManager::instance(), &ClientManager::addCacheDataResponse,
            this, &RequestsHandlerClient::onCacheDataAdditionSucceed);
    connect(ClientManager::instance(), &ClientManager::addUserResponse,
            this, &RequestsHandlerClient::onUserAdditionSucceed);
    connect(ClientManager::instance(), &ClientManager::passwordResponse,
            this, &RequestsHandlerClient::onPasswordDownloadSucceed);
    connect(ClientManager::instance(), &ClientManager::nicknameExistanceResponse,
            this, &RequestsHandlerClient::onNicknameExistanceRequestSucceed);
    connect(ClientManager::instance(), &ClientManager::internalServerErrorResponse,
            this, &RequestsHandlerClient::onInternalServerError);
}


RequestsHandlerClient::~RequestsHandlerClient()
{

}

RequestsHandlerClient *RequestsHandlerClient::instance()
{
    static RequestsHandlerClient *instance = new RequestsHandlerClient;
    return instance;
}

bool RequestsHandlerClient::requestTopTime(int dimension)
{
    QVariant data {QVariant::fromValue(dimension)};
    const net::Package package {data, net::PackageType::TOP_TIME_REQUEST};
    return ClientManager::instance()->sendPackage(package);
}

bool RequestsHandlerClient::requestTopTurns(int dimension)
{
    QVariant data {QVariant::fromValue(dimension)};
    const net::Package package {data, net::PackageType::TOP_TURNS_REQUEST};
    return ClientManager::instance()->sendPackage(package);
}

bool RequestsHandlerClient::requestRecordAddition(const Record &record)
{
    QVariantList dataList {QVariant::fromValue(record.nickname()),
                           QVariant::fromValue(record.time()),
                           QVariant::fromValue(record.turns()),
                           QVariant::fromValue(record.dimension())};
    const net::Package package {QVariant::fromValue(dataList), net::PackageType::ADD_RECORD_REQUEST};
    return ClientManager::instance()->sendPackage(package);
}

bool RequestsHandlerClient::requestRecordAdditionMultiple(const std::vector<DBTypes::DBEntry> &entries)
{
    DBTypes::DBEntry rawData;
    size_t recordParamCount = entries[0].size();
    for (auto record : entries) {
        for(size_t i = 0; i < recordParamCount; ++i) {
            rawData.push_back(std::move(record[i]));
        }
    }
    rawData.push_front(QVariant::fromValue(static_cast<int>(recordParamCount)));
    const net::Package package {QVariant::fromValue(rawData), net::PackageType::ADD_CACHE_DATA_REQUEST};
    return ClientManager::instance()->sendPackage(package);
}




bool RequestsHandlerClient::requestUserAddition(const QString &nickname, const QString &password)
{
    QVariantList dataList {QVariant::fromValue(nickname),QVariant::fromValue(password)};
    const net::Package package {QVariant::fromValue(dataList), net::PackageType::ADD_USER_REQUEST};
    return ClientManager::instance()->sendPackage(package);
}

bool RequestsHandlerClient::requestPassword(const QString &nickname)
{
    QVariant data {QVariant::fromValue(nickname)};
    const net::Package package {data, net::PackageType::PASSWORD_REQUEST};
    return ClientManager::instance()->sendPackage(package);
}

bool RequestsHandlerClient::requestNicknameExistance(const QString &nickname)
{
    QVariant data {QVariant::fromValue(nickname)};
    const net::Package package {data, net::PackageType::NICKNAME_EXISTANCE_REQUEST};
    return ClientManager::instance()->sendPackage(package);
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


void RequestsHandlerClient::onRecordAdditionSucceed(const QVariant &data)
{
    emit recordAdditionRequestCompleted(data.toBool());
}

void RequestsHandlerClient::onCacheDataAdditionSucceed(const QVariant &data)
{
    emit cacheDataAdditionRequestCompleted(data.toBool());
}

void RequestsHandlerClient::onUserAdditionSucceed(const QVariant &data)
{
    emit userAdditionRequestCompleted(data.toBool());
}

void RequestsHandlerClient::onPasswordDownloadSucceed(const QVariant &data)
{
    qDebug() << "Recieved password: ";
    qDebug() << data;
    emit passwordRequestCompleted(data.toString());
}

void RequestsHandlerClient::onNicknameExistanceRequestSucceed(const QVariant &data)
{
    qDebug() << "Recieved user existance responce: ";
    qDebug() << data;
    emit nicknameExistanceRequestCompleted(data.toBool());
}

void RequestsHandlerClient::onInternalServerError(const QVariant &data)
{
    emit internalServerErrorOccured(static_cast<net::InternalServerError>(data.toInt()));

}
