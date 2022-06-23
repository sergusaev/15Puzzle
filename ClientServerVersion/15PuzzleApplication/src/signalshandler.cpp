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
    emit ethalonPasswordChanged();
}

void SignalsHandler::onDimensionChanged(int dimension)
{
    emit dimensionChanged();
}

void SignalsHandler::onNicknameExists()
{
    emit nicknameExists();
}
