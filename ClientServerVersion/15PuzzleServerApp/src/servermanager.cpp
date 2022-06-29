#include "servermanager.h"
#include <QTcpSocket>


ServerManager::ServerManager(const net::ConnectionArgumentsParser &parser)
    : m_parser {parser}
{
    connectSignals();
    const bool listenResult {m_server.listen(QHostAddress {m_parser.hostArgument()},
                                             static_cast<quint16>(m_parser.portArgument().toUInt()))};

    if (!listenResult)
    {
        qCritical() << "Cannot initialize server! Not started!";
    }
}

void ServerManager::onNewConnection()
{
    qDebug() << "New connection!";
    QTcpSocket* clientConnection = m_server.nextPendingConnection();
    if (clientConnection)
    {
        connectSocketSignals(clientConnection);
        m_clients.push_back(clientConnection);
    }
}

void ServerManager::onClientDisconnected()
{
    QObject* senderObject = sender();
    QTcpSocket* socket {qobject_cast<QTcpSocket*>(senderObject)};

    if (!socket)
    {
        return;
    }

    m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), socket),
                    m_clients.end());
    socket->deleteLater();
    qDebug() << "Client disconnected!";
}

void ServerManager::onDataArrived()
{
    QMutexLocker locker(&m_mux);
    QObject* senderObject = sender();
    QTcpSocket* socket {qobject_cast<QTcpSocket*>(senderObject)};

    if (!socket)
    {
        return;
    }

    QDataStream in {socket};
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    forever {
        in.startTransaction();

        net::Package inputPackage;
        in >> inputPackage;

        if (!in.commitTransaction())
        {
            break;
        }

        handlePackage(inputPackage, socket);
    }
}

void ServerManager::notify(const net::Package &package, QTcpSocket *socket)
{
    if (socket)
    {
        socket->write(package.rawData());
    }
}

void ServerManager::handlePackage(net::Package &package, QTcpSocket *socket)
{
    if (!socket)
    {
        qWarning() << "Null socket. What?";
        return;
    }

#ifdef DEBUG_OUTPUT
    QString currPackageType;
    switch(package.type()){
    case net::PackageType::PASSWORD_REQUEST:
        currPackageType = "PASSWORD_REQUEST";
        break;
    case net::PackageType::ADD_USER_REQUEST:
        currPackageType = "ADD_USER_REQUEST";
        break;
    case net::PackageType::TOP_TIME_REQUEST:
        currPackageType = "TOP_TIME_REQUEST";
        break;
    case net::PackageType::TOP_TURNS_REQUEST:
        currPackageType = "TOP_TURNS_REQUEST";
        break;
    case net::PackageType::ADD_RECORD_REQUEST:
        currPackageType = "ADD_RECORD_REQUEST";
        break;
    case net::PackageType::ADD_CACHE_DATA_REQUEST:
        currPackageType = "ADD_CACHE_DATA_REQUEST";
        break;
    case net::PackageType::NICKNAME_EXISTANCE_REQUEST:
        currPackageType = "NICKNAME_EXISTANCE_REQUEST";
        break;
    default:
        currPackageType = "INVALID";
        break;
    }
    qDebug() << "Recieved package with type " << currPackageType;
#endif

    switch (package.type())
    {
    case net::PackageType::PASSWORD_REQUEST:
    {
        m_requestHandler.handlePasswordRequest(package,socket);
        break;
    }
    case net::PackageType::ADD_USER_REQUEST:
    {
        m_requestHandler.handleAddUserRequest(package, socket);
        break;
    }
    case net::PackageType::TOP_TIME_REQUEST:
    {
        m_requestHandler.handleTopTimeRequest(package, socket);
        break;
    }
    case net::PackageType::TOP_TURNS_REQUEST:
    {
        m_requestHandler.handleTopTurnsRequest(package, socket);
        break;
    }
    case net::PackageType::ADD_RECORD_REQUEST:
    {
        m_requestHandler.handleAddRecordRequest(package, socket);
        break;
    }
    case net::PackageType::ADD_CACHE_DATA_REQUEST:
    {
        m_requestHandler.handleAddCacheDataRequest(package, socket);
        break;
    }
    case net::PackageType::NICKNAME_EXISTANCE_REQUEST:
    {
        m_requestHandler.handleNicknameExistanceRequest(package, socket);
        break;
    }
    default: {
        qWarning() << "Invalid package recieved!";
    }
    }
}

void ServerManager::connectSignals()
{
    connect(&m_server, &QTcpServer::newConnection,
            this, &ServerManager::onNewConnection);
    connect(&m_requestHandler, &RequestHandlerServer::passwordRequestCompleted,
            this, &ServerManager::notify);
    connect(&m_requestHandler, &RequestHandlerServer::nicknameExistanceRequestCompleted,
            this, &ServerManager::notify);
    connect(&m_requestHandler, &RequestHandlerServer::userAdditionRequestCompleted,
            this, &ServerManager::notify);
    connect(&m_requestHandler, &RequestHandlerServer::topTimeRequestCompleted,
            this, &ServerManager::notify);
    connect(&m_requestHandler, &RequestHandlerServer::topTurnsRequestCompleted,
            this, &ServerManager::notify);
    connect(&m_requestHandler, &RequestHandlerServer::recordAdditionRequestCompleted,
            this, &ServerManager::notify);
    connect(&m_requestHandler, &RequestHandlerServer::cacheDataAdditionRequestCompleted,
            this, &ServerManager::notify);
}

void ServerManager::connectSocketSignals(QTcpSocket* socket)
{
    connect(socket, &QAbstractSocket::disconnected,
            this, &ServerManager::onClientDisconnected);
    connect(socket, &QAbstractSocket::readyRead,
            this, &ServerManager::onDataArrived);
}
