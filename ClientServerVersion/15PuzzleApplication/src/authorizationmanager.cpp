#include "authorizationmanager.h"

AuthorizationManager::AuthorizationManager()
    : m_dimension (2)
{
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::passwordRequestCompleted,
            this, &AuthorizationManager::onPasswordDownloaded);
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::userAdditionRequestCompleted,
            this, &AuthorizationManager::onUserAdded);
    connect(ClientManager::instance(), &ClientManager::connectionStateChanged,
            this, &AuthorizationManager::onConnectionStateChanged);
}


AuthorizationManager *AuthorizationManager::instance()
{
    static AuthorizationManager *instance = new AuthorizationManager;
    return instance;
}

AuthorizationManager::~AuthorizationManager()

{

}

const QString &AuthorizationManager::nickname() const
{
    return m_nickname;
}

void AuthorizationManager::setNickname(const QString &newNickname)
{
    if (m_nickname == newNickname)
        return;
    m_nickname = newNickname;
    emit nicknameChanged(m_nickname);
}

const QString &AuthorizationManager::password() const
{
    return m_password;
}

void AuthorizationManager::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged(m_password);
}

const QString &AuthorizationManager::ethalonPassword() const
{
    return m_ethalonPassword;
}

void AuthorizationManager::setEthalonPassword(const QString &newEthalonPassword)
{
    if (m_ethalonPassword == newEthalonPassword)
        return;
    m_ethalonPassword = newEthalonPassword;
    emit ethalonPasswordChanged(m_ethalonPassword);
    qDebug() << "Ethalon password: " + ethalonPassword();
}

int AuthorizationManager::dimension() const
{
    return m_dimension;
}

void AuthorizationManager::setDimension(int newDimension)
{
    if (m_dimension == newDimension)
        return;
    m_dimension = newDimension;
    emit dimensionChanged(m_dimension);
}

bool AuthorizationManager::connectionState() const
{
    return m_connectionState;
}

void AuthorizationManager::setConnectionState(bool newConnectionState)
{
    if (m_connectionState == newConnectionState)
        return;
    m_connectionState = newConnectionState;
    emit connectionStateChanged(m_connectionState);
}


void AuthorizationManager::addNewUser(const QString &nickname, const QString &password)
{
    if(!RequestsHandlerClient::instance()->requestUserAddition(nickname, password)) {      
        qDebug() << "Failed to access remote database, try again";
        emit noServerConnection();
    } else {
        qDebug() << "Addition request successfully sent";
    }

}

void AuthorizationManager::requestUserPassword(const QString &password)
{
    if(!RequestsHandlerClient::instance()->requestPassword(password)) {
        qDebug() << "Failed to access remote database, try again";
        emit noServerConnection();
    } else {
        qDebug() << "Password request successfully sent";
    }
}

void AuthorizationManager::onConnectionStateChanged(net::ConnectionState state)
{
    switch (state)
    {
    case net::ConnectionState::Connected:
        setConnectionState(true);
        break;
    default:
        setConnectionState(false);
        break;
    }

}


void AuthorizationManager::onUserAdded(bool additionResult)
{

}

void AuthorizationManager::onPasswordDownloaded(const QString &password)
{
    qDebug() << "In AuthorizationManager recieved password: " + password;

    if(password == ethalonPassword()) {
        return;
    }
    setEthalonPassword(password);
}



