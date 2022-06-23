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

signals:
    void noServerConnection();
    void connectionStateChanged(bool connectionState);
    void authorizationPageStateChanged(int newAuthorizationPageState);
    void nicknameChanged();
    void passwordChanged();
    void ethalonPasswordChanged();
    void dimensionChanged();
    void nicknameExists();
};

#endif // SIGNALSHANDLER_H
