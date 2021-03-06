#include "signalshandler.h"
#include "authorizationmanager.h"


SignalsHandler::~SignalsHandler()
{

}

SignalsHandler *SignalsHandler::instance()
{
    static SignalsHandler *instance = new SignalsHandler;
    return instance;
}

SignalsHandler::SignalsHandler()
{
    connect(AuthorizationManager::instance(),&AuthorizationManager::noServerConnection,
            this, &SignalsHandler::onNoServerConnection);
    connect(AuthorizationManager::instance(),&AuthorizationManager::connectionStateChanged,
            this, &SignalsHandler::onConnectionStateChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::newUserChanged,
            this, &SignalsHandler::onNewUserChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::authorizationPageStateChanged,
            this, &SignalsHandler::onAuthorizathionPageStateChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::nicknameChanged,
            this, &SignalsHandler::onNicknameChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::passwordChanged,
            this, &SignalsHandler::onPasswordChanged);
    connect(AuthorizationManager::instance(),&AuthorizationManager::passwordValidationCompleted,
            this, &SignalsHandler::onPasswordValidationSucceed);
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
    connect(AuthorizationManager::instance(),&AuthorizationManager::userAdded,
            this, &SignalsHandler::onUserAdded);

}



void SignalsHandler::onNoServerConnection()
{
    emit noServerConnection();
}

void SignalsHandler::onConnectionStateChanged(bool connectionState)
{
    emit connectionStateChanged(connectionState);
}

void SignalsHandler::onNewUserChanged(bool newUser)
{
    emit newUserChanged(newUser);
}



void SignalsHandler::onNicknameChanged(const QString &nickname)
{
    emit nicknameChanged(nickname);
}

void SignalsHandler::onAuthorizathionPageStateChanged(int newAuthorizationPageState)
{
    emit authorizationPageStateChanged(newAuthorizationPageState);
}

void SignalsHandler::onPasswordChanged(const QString &password)
{
    emit passwordChanged(password);
}

void SignalsHandler::onPasswordValidationSucceed(const bool validationResult)
{
    emit passwordValidationCompleted(validationResult);
}



void SignalsHandler::onDimensionChanged(int dimension)
{
    emit dimensionChanged(dimension);
}

void SignalsHandler::onNicknameExists(bool exists)
{
    emit nicknameExists(exists);
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

void SignalsHandler::onCacheDataAdditionInternalServerError()
{
    emit cacheDataAdditionInternalServerError();
}

void SignalsHandler::onUserAdded()
{
    emit userSuccessfullyAdded();
}
