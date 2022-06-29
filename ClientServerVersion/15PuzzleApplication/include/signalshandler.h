#ifndef SIGNALSHANDLER_H
#define SIGNALSHANDLER_H

#include "networktypes.h"
#include <QObject>

class SignalsHandler : public QObject
{
    Q_OBJECT
public:
    ~SignalsHandler();

    static SignalsHandler *instance();

private slots:
    void onNoServerConnection();
    void onConnectionStateChanged(bool connectionState);
    void onNewUserChanged(bool newUser);
    void onNicknameChanged(const QString &nickname);
    void onAuthorizathionPageStateChanged(int newAuthorizationPageState);
    void onPasswordChanged(const QString &password);
    void onEthalonPasswordChanged(const QString &ethalonPassword);
    void onDimensionChanged(int dimension);
    void onNicknameExists(bool exists);
    void onNicknameExistanceInternalServerError();
    void onPasswordInternalServerError();
    void onUserAdditionInternalServerError();
    void onCacheDataAdditionInternalServerError();


signals:
    void noServerConnection();
    void connectionStateChanged(bool connectionState);
    void newUserChanged(bool newUser);
    void authorizationPageStateChanged(int newAuthorizationPageState);
    void nicknameChanged(const QString &nickname);
    void passwordChanged(const QString &password);
    void ethalonPasswordChanged(const QString &ethalonPassword);
    void dimensionChanged(int dimension);
    void nicknameExists(bool exists);
    void nicknameExistanceInternalServerError();
    void passwordInternalServerError();
    void userAdditionInternalServerError();
    void cacheDataAdditionInternalServerError();

private:
    SignalsHandler();

};

#endif // SIGNALSHANDLER_H
