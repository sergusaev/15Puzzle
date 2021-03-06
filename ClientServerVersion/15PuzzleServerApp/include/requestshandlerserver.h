#ifndef REQUESTSHANDLERSERVER_H
#define REQUESTSHANDLERSERVER_H

#include <QObject>
#include "recordsmanager.h"
#include <package.h>

class QTcpSocket;

class RequestHandlerServer:public QObject {
    Q_OBJECT

public:
    RequestHandlerServer();
    ~RequestHandlerServer();

    void handleNicknameExistanceRequest(const net::Package& packageData,QTcpSocket* socket);
    void handlePasswordValidityRequest(const net::Package& packageData,QTcpSocket* socket);
    void handleAddUserRequest(const net::Package& packageData, QTcpSocket* socket);
    void handleTopTimeRequest(const net::Package& packageData, QTcpSocket* socket);
    void handleTopTurnsRequest(const net::Package& packageData, QTcpSocket* socket);
    void handleAddRecordRequest(const net::Package& packageData, QTcpSocket* socket);
    void handleAddCacheDataRequest(const net::Package& packageData, QTcpSocket* socket);

signals:
    void nicknameExistanceRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void passwordValidityRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void userAdditionRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void topTimeRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void topTurnsRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void recordAdditionRequestCompleted(const net::Package& packageData, QTcpSocket* socket);
    void cacheDataAdditionRequestCompleted(const net::Package& packageData, QTcpSocket* socket);

private:
    RecordsManager m_recordsManager;
};

#endif // REQUESTSHANDLERSERVER_H
