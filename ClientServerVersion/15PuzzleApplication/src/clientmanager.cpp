#include "clientmanager.h"
#include <QTimer>

ClientManager::ClientManager()
{
    connectSocketSignals();

}

ClientManager::~ClientManager()
{

}

ClientManager *ClientManager::instance()
{
    static ClientManager *instance = new ClientManager();
    return instance;
}

bool ClientManager::sendPackage(const net::Package &package)
{
    if(m_state == net::ConnectionState::Connected) {
        qDebug()<<"Connection state: connected";
    } else {
        qDebug()<<"Connection state: disconnected";
        return false;
    }
    m_serverSocket.write(package.rawData());
    return true;
}

void ClientManager::onSocketError(QAbstractSocket::SocketError socketError)
{
    qCritical() << "Socket error happened: " << socketError;

    QTimer::singleShot(reconnectionTime(), this, &ClientManager::connectToServer);

    emit reconnectionTimerStarted();
}

void ClientManager::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket state changed: " << socketState;

    switch (socketState)
    {
    case QAbstractSocket::SocketState::BoundState:
    case QAbstractSocket::SocketState::ConnectedState:
    {
        m_state = net::ConnectionState::Connected;
        break;
    }
    case QAbstractSocket::SocketState::ClosingState:
    case QAbstractSocket::SocketState::UnconnectedState:
    {
        m_state = net::ConnectionState::Disconnected;
        break;
    }
    default:
    {
        m_state = net::ConnectionState::Connecting;
    }
    }

    emit connectionStateChanged(m_state);
}

void ClientManager::onDataRecieved()
{
    qDebug() << "New data recieved";
    QMutexLocker locker(&m_mux);
    QDataStream in {&m_serverSocket};
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    forever {
        in.startTransaction();

        net::Package inputPackage;
        in >> inputPackage;

        if (!in.commitTransaction())
        {
            break;
        }
        handlePackage(inputPackage);
    }
}

void ClientManager::connectToServer()
{
    qDebug() << "Connecting to server...";

    if (!m_connectionSettings)
    {
        qCritical() << "Cannot connect! Connection settings are not initialized!";
        return;
    }

    m_serverSocket.connectToHost(m_connectionSettings->hostArgument(),
                                 static_cast<quint16>(m_connectionSettings->portArgument().toUInt()));
}

void ClientManager::connectSocketSignals()
{
    connect(&m_serverSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &ClientManager::onSocketError);
    connect(&m_serverSocket, &QAbstractSocket::stateChanged,
            this, &ClientManager::onSocketStateChanged);
    connect(&m_serverSocket, &QAbstractSocket::readyRead,
            this, &ClientManager::onDataRecieved);
}

void ClientManager::handlePackage(net::Package &package)
{
#ifdef DEBUG_OUTPUT
    QString currPackageType;
    switch(package.type()){
    case net::PackageType::PASSWORD_VALIDATION_RESPONSE:
        currPackageType = "PASSWORD_VALIDATION_RESPONCE";
        break;
    case net::PackageType::ADD_USER_RESPONSE:
        currPackageType = "ADD_USER_RESPONCE";
        break;
    case net::PackageType::TOP_TIME_RESPONSE:
        currPackageType = "TOP_TIME_RESPONCE";
        break;
    case net::PackageType::TOP_TURNS_RESPONSE:
        currPackageType = "TOP_TURNS_RESPONCE";
        break;
    case net::PackageType::ADD_RECORD_RESPONSE:
        currPackageType = "ADD_RECORD_RESPONCE";
        break;
    case net::PackageType::ADD_CACHE_DATA_RESPONSE:
        currPackageType = "ADD_CACHE_DATA_RESPONSE";
        break;
    case net::PackageType::NICKNAME_EXISTANCE_RESPONSE:
        currPackageType = "NICKNAME_EXISTANCE_RESPONCE";
        break;
    case net::PackageType::INTERNAL_SERVER_ERROR:
        currPackageType = "INTERNAL_SERVER_ERROR";
        break;
    default:
        currPackageType = "INVALID";
        break;
    }
    qDebug() << "Recieved package with type " << currPackageType;
#endif

    switch (package.type())
    {
    case net::PackageType::TOP_TIME_RESPONSE:
    {
        handleTopTimeResponsePackage(package);
        break;
    }
    case net::PackageType::TOP_TURNS_RESPONSE:
    {
        handleTopTurnsResponsePackage(package);
        break;
    }
    case net::PackageType::ADD_RECORD_RESPONSE:
    {
        handleAddRecordResponsePackage(package);
        break;
    }
    case net::PackageType::ADD_CACHE_DATA_RESPONSE:
    {
        handleAddCacheDataResponsePackage(package);
        break;
    }
    case net::PackageType::ADD_USER_RESPONSE:
    {
        handleAddUserResponsePackage(package);
        break;
    }
    case net::PackageType::PASSWORD_VALIDATION_RESPONSE:
    {
        handlePasswordValidityResponsePackage(package);
        break;
    }
    case net::PackageType::NICKNAME_EXISTANCE_RESPONSE:
    {
        handleNicknameExistanceResponsePackage(package);
        break;
    }
    case net::PackageType::INTERNAL_SERVER_ERROR:
    {
        handleInternalServerErrorPackage(package);
        break;
    }
    default: {
        qWarning() << "Invalid package!";
    }
    }
}

void ClientManager::handleTopTimeResponsePackage(const net::Package &package)
{
    std::vector<QVariant> data;
    QVariant packageData {package.data()};
    QSequentialIterable recordsData {packageData.value<QSequentialIterable>()};

    for (auto& entry : recordsData)
    {
        data.push_back(std::move(entry));
    }

    emit topTimeResponse(data);
}

void ClientManager::handleTopTurnsResponsePackage(const net::Package &package)
{
    std::vector<QVariant> data;
    QVariant packageData {package.data()};
    QSequentialIterable recordsData {packageData.value<QSequentialIterable>()};

    for (auto& entry : recordsData)
    {
        data.push_back(std::move(entry));
    }

    emit topTurnsResponse(data);
}


void ClientManager::handleAddRecordResponsePackage(const net::Package &package)
{

    emit addRecordResponse(package.data());
}

void ClientManager::handleAddCacheDataResponsePackage(const net::Package &package)
{
    qDebug() << "CacheDataResponse package data: " << package.data();
    emit addCacheDataResponse(package.data());
}

void ClientManager::handleAddUserResponsePackage(const net::Package &package)
{
    emit addUserResponse(package.data());
}

void ClientManager::handlePasswordValidityResponsePackage(const net::Package &package)
{
    emit passwordValidityResponse(package.data());
}

void ClientManager::handleNicknameExistanceResponsePackage(const net::Package &package)
{
    emit nicknameExistanceResponse(package.data());
}

void ClientManager::handleInternalServerErrorPackage(const net::Package &package)
{
    emit internalServerErrorResponse(package.data());
}


void ClientManager::setConnectionSettings(const net::ConnectionArgumentsParser &connectionSettings)
{
    m_connectionSettings = &connectionSettings;
    connectToServer();
}
