#include "authorizationmanager.h"

AuthorizationManager::AuthorizationManager()
    : m_dimension (2)
{
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::internalServerErrorOccured,
            this, &AuthorizationManager::onInternalServerErrorOccured);
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::passwordValidationRequestCompleted,
            this, &AuthorizationManager::onPasswordValidationRequestCompleted);
    connect(RequestsHandlerClient::instance(), &RequestsHandlerClient::userAdditionRequestCompleted,
            this, &AuthorizationManager::onUserAdded);
    connect(ClientManager::instance(), &ClientManager::connectionStateChanged,
            this, &AuthorizationManager::onConnectionStateChanged);
    connect(&m_nicknameHint, &NicknameHint::nicknameExists,
            this, &AuthorizationManager::onNicknameExists);
}




 int AuthorizationManager::authorizationPageState() const
{
    return static_cast<int>(m_authorizathionPageState);
}

void AuthorizationManager::setAuthorizationPageState(int newAuthorizathionPageState)
{
    m_authorizathionPageState = static_cast<AuthorizationPageState>(newAuthorizathionPageState);
    emit authorizationPageStateChanged(newAuthorizathionPageState);
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
    m_nickname = newNickname;
    emit nicknameChanged(m_nickname);
}

const QString &AuthorizationManager::password() const
{
    return m_password;
}

void AuthorizationManager::setPassword(const QString &newPassword)
{

    m_password = newPassword;
    emit passwordChanged(m_password);
}


int AuthorizationManager::dimension() const
{
    return m_dimension;
}

void AuthorizationManager::setDimension(int newDimension)
{
    m_dimension = newDimension;
    emit dimensionChanged(m_dimension);
}

bool AuthorizationManager::connectionState() const
{
    return m_connectToServer;
}

void AuthorizationManager::setConnectionState(bool newConnectionState)
{
    m_connectToServer = newConnectionState;
    emit connectionStateChanged(m_connectToServer);
}

bool AuthorizationManager::newUser() const
{
    return m_newUser;
}

void AuthorizationManager::setNewUser(bool newNewUser)
{
    m_newUser = newNewUser;
    emit newUserChanged(newNewUser);
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

void AuthorizationManager::validatePassword(const QString &nickname, const QString &password)
{
    if(!RequestsHandlerClient::instance()->requestPasswordValidation(nickname, password)) {
        qDebug() << "Failed to access remote database, try again";
        emit noServerConnection();
    } else {
        qDebug() << "Password validity request on nickname " + nickname + " successfully sent";

    }
}

void AuthorizationManager::checkNicknameExistance(const QString &nickname)
{
    if(!m_nicknameHint.requestNicknameExistanceCheck(nickname)) {
        qDebug() << "Failed to access remote database, try again";
        emit noServerConnection();
    } else {
        qDebug() << "Nickname existance request successfully sent";
    }
}

QByteArray AuthorizationManager::encodePasswordFromQml(const QString &password)
{
    return RequestsHandlerClient::instance()->encodePassword(password);
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
    emit connectionStateChanged(m_connectToServer);
}

void AuthorizationManager::onInternalServerErrorOccured(net::InternalServerError error)
{
    switch(error) {
    case net::InternalServerError::NICKNAME_EXISTANCE_ERROR :
        emit nicknameExistanceInternalServerError();
        break;
    case net::InternalServerError::PASSWORD_ERROR :
        emit passwordInternalServerError();
        break;
    case net::InternalServerError::USER_ADDITION_ERROR :
        emit userAdditionInternalServerError();
        break;
    case net::InternalServerError::TOP_TIME_ERROR:
        emit topTimeInternalServerError();
        break;
    case net::InternalServerError::TOP_TURNS_ERROR:
        emit topTurnsInternalServerError();
        break;
    case net::InternalServerError::RECORD_ADDITION_ERROR :
        emit recordAdditionInternalServerError();
        break;
    case net::InternalServerError::CACHE_DATA_ADDITION_ERROR :
        emit cacheDataAdditionInternalServerError();
        break;
    }
}


void AuthorizationManager::onUserAdded(bool additionResult)
{
    if(additionResult) {
        emit userAdded();
    }
}

void AuthorizationManager::onPasswordValidationRequestCompleted(const bool validationResult)
{
    qDebug() << "In AuthorizationManager recieved password validation result: "  << validationResult;
    emit passwordValidationCompleted(validationResult);

}

void AuthorizationManager::onNicknameExists(bool exists)
{
    emit nicknameExists(exists);
}



