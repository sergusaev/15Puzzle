#include "requestshandlerserver.h"
#include <QDebug>

RequestHandlerServer::RequestHandlerServer()
{

}

RequestHandlerServer::~RequestHandlerServer()
{

}

void RequestHandlerServer::handleNicknameExistanceRequest(const net::Package &packageData, QTcpSocket *socket)
{
    bool requestResult;
    QVariant data;
    std::tie(requestResult, data) = m_recordsManager.findNickname(packageData.data());
    if(requestResult) {
        net::Package resultPackage {data, net::PackageType::NICKNAME_EXISTANCE_RESPONSE};
        emit nicknameExistanceRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue(static_cast<int>(net::InternalServerError::NICKNAME_EXISTANCE_ERROR)),
                                    net::PackageType::INTERNAL_SERVER_ERROR};
        emit nicknameExistanceRequestCompleted(resultPackage, socket);
    }
}

void RequestHandlerServer::handlePasswordValidityRequest(const net::Package &packageData, QTcpSocket *socket)
{
    bool requestResult;
    QVariant data;
    std::tie(requestResult, data) = m_recordsManager.checkPasswordValidity(packageData.data());
    if(requestResult) {
        net::Package resultPackage {data, net::PackageType::PASSWORD_VALIDATION_RESPONSE};
        emit passwordValidityRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue(static_cast<int>(net::InternalServerError::PASSWORD_ERROR)),
                                    net::PackageType::INTERNAL_SERVER_ERROR};
        emit passwordValidityRequestCompleted(resultPackage, socket);
    }

#ifdef DEBUG_OUTPUT
    if(requestResult) {
        qDebug() << "Requested password validation result successfully sent";
        qDebug() << data;
    } else {
        qDebug() << "Internal server error";
    }
#endif
}


void RequestHandlerServer::handleAddUserRequest(const net::Package& packageData, QTcpSocket *socket)
{
    QVariantList dataList = packageData.data().toList();
    bool additionResult {m_recordsManager.addUser(dataList)};
    if(additionResult) {
        net::Package resultPackage {QVariant::fromValue(additionResult), net::PackageType::ADD_USER_RESPONSE};
        emit userAdditionRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue(static_cast<int>(net::InternalServerError::USER_ADDITION_ERROR)), net::PackageType::INTERNAL_SERVER_ERROR};
        emit userAdditionRequestCompleted(resultPackage, socket);
    }

#ifdef DEBUG_OUTPUT
    if(additionResult) {
        qDebug() << "User successfully added";
        qDebug() << dataList;
    } else {
        qDebug() << "Internal server error";
    }
#endif

}

void RequestHandlerServer::handleTopTimeRequest(const net::Package &packageData, QTcpSocket *socket)
{

    bool result;
    std::vector<QVariant> entries;
    std::tie(result, entries) = m_recordsManager.getTopTime(packageData.data());
    if(result) {
        QVariantList dataList;
        std::copy (std::make_move_iterator(entries.begin()),
                   std::make_move_iterator(entries.end()),
                   std::back_inserter(dataList));
        net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::TOP_TIME_RESPONSE};
        emit topTimeRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue(static_cast<int>(net::InternalServerError::TOP_TIME_ERROR)),
                                    net::PackageType::INTERNAL_SERVER_ERROR};
        emit topTimeRequestCompleted(resultPackage, socket);
        return;
    }

#ifdef DEBUG_OUTPUT
    if(result) {
        qDebug() << "Top time successfully sent";
    } else {
        qDebug() << "Internal server error";
    }
#endif
}

void RequestHandlerServer::handleTopTurnsRequest(const net::Package &packageData, QTcpSocket *socket)
{
    bool result;
    std::vector<QVariant> entries;
    std::tie(result, entries) = m_recordsManager.getTopTurns(packageData.data());
    if(result) {
        QVariantList dataList;
        std::copy (std::make_move_iterator(entries.begin()),
                   std::make_move_iterator(entries.end()),
                   std::back_inserter(dataList));
        net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::TOP_TURNS_RESPONSE};
        emit topTimeRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue(static_cast<int>(net::InternalServerError::TOP_TURNS_ERROR)),
                                    net::PackageType::INTERNAL_SERVER_ERROR};
        emit topTimeRequestCompleted(resultPackage, socket);
        return;
    }

#ifdef DEBUG_OUTPUT
    if(result) {
        qDebug() << "Top turns successfully sent";
    } else {
        qDebug() << "Internal server error";
    }
#endif

}

void RequestHandlerServer::handleAddRecordRequest(const net::Package& packageData, QTcpSocket *socket)
{
    QVariantList dataList = packageData.data().toList();
    bool additionResult {m_recordsManager.addRecord(dataList)};
    if(additionResult) {
        net::Package resultPackage {QVariant::fromValue(additionResult), net::PackageType::ADD_RECORD_RESPONSE};
        emit userAdditionRequestCompleted(resultPackage, socket);
    } else {
        dataList.push_front(QVariant::fromValue(static_cast<int>(net::InternalServerError::RECORD_ADDITION_ERROR)));
        net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::INTERNAL_SERVER_ERROR};
        emit userAdditionRequestCompleted(resultPackage, socket);
    }

#ifdef DEBUG_OUTPUT
    if(additionResult) {
        qDebug() << "Record successfully added";
        qDebug() << dataList;
    } else {
        qDebug() << "Internal server error";
    }
#endif

}

void RequestHandlerServer::handleAddCacheDataRequest(const net::Package &packageData, QTcpSocket *socket)
{
    QVariantList cacheDataList = packageData.data().toList();
    int paramCount = cacheDataList.front().toInt();
    cacheDataList.pop_front();
    bool additionResult {m_recordsManager.addRecordMultiple(cacheDataList, paramCount)};
    if(additionResult) {
        net::Package resultPackage {QVariant::fromValue(additionResult), net::PackageType::ADD_CACHE_DATA_RESPONSE};
        emit cacheDataAdditionRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue(static_cast<int>(net::InternalServerError::CACHE_DATA_ADDITION_ERROR)), net::PackageType::INTERNAL_SERVER_ERROR};
        emit cacheDataAdditionRequestCompleted(resultPackage, socket);
    }

#ifdef DEBUG_OUTPUT
    if(additionResult) {
        qDebug() << "Cache data successfully added";
        qDebug() << cacheDataList;
    } else {
        qDebug() << "Internal server error";
    }
#endif
}



