#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <networktypes.h>
#include <connectionargumentsparser.h>
#include "record.h"
#include <package.h>
#include <QMutex>

class ClientManager : public QObject
{
    Q_OBJECT
public:

    ~ClientManager();

    static ClientManager *instance();

    constexpr static std::chrono::milliseconds reconnectionTime() {
        return std::chrono::seconds {5};
    }

    bool sendPackage(const net::Package& package);
    void setConnectionSettings(const net::ConnectionArgumentsParser &connectionSettings);

signals:
    void topTimeResponse(const std::vector<QVariant>& data);
    void topTurnsResponse(const std::vector<QVariant>& data);
    void addRecordResponse(const QVariant& data);
    void addUserResponse(const QVariant& data);
    void passwordValidityResponse(const QVariant& data);
    void nicknameExistanceResponse(const QVariant& data);
    void internalServerErrorResponse(const QVariant& data);
    void addCacheDataResponse(const QVariant& data);


    void connectionStateChanged(net::ConnectionState state);
    void reconnectionTimerStarted();

private slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onDataRecieved();

private:
    ClientManager();

    void connectToServer();
    void connectSocketSignals();

    void handlePackage(net::Package& package);
    void handleTopTimeResponsePackage(const net::Package& package);
    void handleTopTurnsResponsePackage(const net::Package& package);
    void handleAddRecordResponsePackage(const net::Package& package);
    void handleAddCacheDataResponsePackage(const net::Package& package);
    void handleAddUserResponsePackage(const net::Package& package);
    void handlePasswordValidityResponsePackage(const net::Package& package);
    void handleNicknameExistanceResponsePackage(const net::Package& package);
    void handleInternalServerErrorPackage(const net::Package& package);

    const net::ConnectionArgumentsParser* m_connectionSettings {nullptr};
    net::ConnectionState m_state;
    QTcpSocket m_serverSocket;
    QMutex m_mux;
};


#endif // CLIENTMANAGER_H
