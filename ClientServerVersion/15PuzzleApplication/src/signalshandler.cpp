#include "signalshandler.h"
#include "authorizationmanager.h"

SignalsHandler::SignalsHandler()
{
    connect(AuthorizationManager::instance(),&AuthorizationManager::noServerConnection,
            this, &SignalsHandler::onNoServerConnection);
    connect(AuthorizationManager::instance(),&AuthorizationManager::connectionStateChanged,
            this, &SignalsHandler::onConnectionStateChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::authorizationPageStateChanged,
            this, &SignalsHandler::onAuthorizathionPageStateChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::nicknameChanged,
            this, &SignalsHandler::onNicknameChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::passwordChanged,
            this, &SignalsHandler::onPasswordChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::ethalonPasswordChanged,
            this, &SignalsHandler::onEthalonPasswordChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::dimensionChanged,
            this, &SignalsHandler::onDimensionChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::nicknameExists,
            this, &SignalsHandler::onNicknameExists);
    connect(AuthorizationManager::instance(),&AuthorizationManager::nicknameExistanceInternalServerError,
            this, &SignalsHandler::onNicknameExistanceInternalServerError);
    connect(AuthorizationManager::instance(),&AuthorizationManager::passwordInternalServerError,
            this, &SignalsHandler::onPasswordInternalServerError);
    connect(AuthorizationManager::instance(),&AuthorizationManager::userAdditionInternalServerError,
            this, &SignalsHandler::onUserAdditionInternalServerError);

}

void SignalsHandler::onNoServerConnection()
{
    emit noServerConnection();
}

void SignalsHandler::onConnectionStateChanged(bool connectionState)
{
    emit connectionStateChanged(connectionState);
}

void SignalsHandler::onNicknameChanged(const QString &nickname)
{
    emit nicknameChanged();
}

void SignalsHandler::onAuthorizathionPageStateChanged(int newAuthorizationPageState)
{
    emit authorizationPageStateChanged(newAuthorizationPageState);
}

void SignalsHandler::onPasswordChanged(const QString &password)
{
    emit passwordChanged();
}

void SignalsHandler::onEthalonPasswordChanged(const QString &ethalonPassword)
{
    emit ethalonPasswordChanged(ethalonPassword);
}

void SignalsHandler::onDimensionChanged(int dimension)
{
    emit dimensionChanged();
}

void SignalsHandler::onNicknameExists()
{
    emit nicknameExists();
}

void SignalsHandler::onNicknameExistanceInternalServerError()
{
    emit nicknameExistanceInternalServerError();
}

void SignalsHandler::onPasswordInternalServerError()
{
    emit passwordInternalServerError();
}

void SignalsHandler::onUserAdditionInternalServerError()
{
    emit userAdditionInternalServerError();
}
