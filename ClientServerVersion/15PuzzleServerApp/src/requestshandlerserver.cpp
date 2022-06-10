#include "requestshandlerserver.h"
#include <QDebug>

void RequestHandlerServer::handlePasswordRequest(const net::Package &packageData, QTcpSocket *socket)
{
    bool requestResult;
    QVariant data;
    std::tie(requestResult, data) = m_recordsManager.getPassword(packageData.data());
    if(requestResult) {
        net::Package resultPackage {data, net::PackageType::PASSWORD_RESPONSE};
        emit passwordRequestCompleted(resultPackage, socket);
    } else {
        net::Package resultPackage {QVariant::fromValue("Error while getting password"), net::PackageType::INTERNAL_SERVER_ERROR};
        emit passwordRequestCompleted(resultPackage, socket);
    }

    //    if (browseResult)
    //    {
    //        QVariant dataList;
    //        std::copy (std::make_move_iterator(data.begin()),
    //                   std::make_move_iterator(data.end()),
    //                   std::back_inserter(dataList));
}


void RequestHandlerServer::handleAddUserRequest(const net::Package& packageData, QTcpSocket *socket)
{
    QVariantList dataList = packageData.data().toList();
    DBTypes::DBIndex index = m_recordsManager.requestContactAddition(dataList);
    dataList.push_front(index);
    net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::ADD_USER_RESPONSE};
    emit userAdditionRequestCompleted(resultPackage, socket);
}

void RequestHandlerServer::handleTopTimeRequest(const net::Package &packageData, QTcpSocket *socket)
{
    DBTypes::DBIndex index = packageData.data().toInt();
    bool removalResult = m_recordsManager.requestContactRemoval(index);
    if(removalResult) {
        net::Package resultPackage {QVariant::fromValue(index), net::PackageType::TOP_TIME_RESPONSE};
        emit topTimeRequestCompleted(resultPackage, socket);
        qWarning() << "Contact removal succeed! DB index of deleted contact:" << index;
    } else {
        qCritical() << "Contact removal failed! DB index of contact failed to delete:" << index;
        return;
    }
}
void RequestHandlerServer::handleTopTurnsRequest(const net::Package &packageData, QTcpSocket *socket)
{
    DBTypes::DBIndex index = packageData.data().toInt();
    bool removalResult = m_recordsManager.requestContactRemoval(index);
    if(removalResult) {
        net::Package resultPackage {QVariant::fromValue(index), net::PackageType::TOP_TURNS_RESPONSE};
        emit topTurnsRequestCompleted(resultPackage, socket);
        qWarning() << "Contact removal succeed! DB index of deleted contact:" << index;
    } else {
        qCritical() << "Contact removal failed! DB index of contact failed to delete:" << index;
        return;
    }
}

void RequestHandlerServer::handleAddRecordRequest(const net::Package& packageData, QTcpSocket *socket)
{
    QVariantList dataList = packageData.data().toList();
    DBTypes::DBIndex index = m_recordsManager.requestContactAddition(dataList);
    dataList.push_front(index);
    net::Package resultPackage {QVariant::fromValue(dataList), net::PackageType::ADD_RECORD_RESPONSE};
    emit recordAdditionRequestCompleted(resultPackage, socket);
}



