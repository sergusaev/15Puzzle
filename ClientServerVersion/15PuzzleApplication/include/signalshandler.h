#ifndef SIGNALSHANDLER_H
#define SIGNALSHANDLER_H

#include "networktypes.h"
#include <QObject>

class SignalsHandler : public QObject
{
    Q_OBJECT
public:
    SignalsHandler();

private slots:
    void onNoServerConnection();
    void onConnectionStateChanged(bool connectionState);
    void onNicknameChanged(const QString &nickname);
    void onAuthorizathionPageStateChanged(int newAuthorizationPageState);
    void onPasswordChanged(const QString &password);
    void onEthalonPasswordChanged(const QString &ethalonPassword);
    void onDimensionChanged(int dimension);
    void onNicknameExists();
    void onNicknameExistanceInternalServerError();
    void onPasswordInternalServerError();
    void onUserAdditionInternalServerError();

signals:
    void noServerConnection();
    void connectionStateChanged(bool connectionState);
    void authorizationPageStateChanged(int newAuthorizationPageState);
    void nicknameChanged();
    void passwordChanged();
    void ethalonPasswordChanged(const QString &ethalonPassword);
    void dimensionChanged();
    void nicknameExists();
    void nicknameExistanceInternalServerError();
    void passwordInternalServerError();
    void userAdditionInternalServerError();

};

#endif // SIGNALSHANDLER_H
