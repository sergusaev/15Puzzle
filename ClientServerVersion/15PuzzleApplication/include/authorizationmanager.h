#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>
#include "cachehandler.h"
#include <QtQml>
#include "requestshandlerclient.h"
#include "nicknamehint.h"


class AuthorizationManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int authorizationPageState READ authorizationPageState WRITE setAuthorizationPageState NOTIFY authorizationPageStateChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString ethalonPassword READ ethalonPassword WRITE setEthalonPassword NOTIFY ethalonPasswordChanged)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(bool connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)

public:
    static AuthorizationManager *instance();
    ~AuthorizationManager();

    int authorizationPageState() const;
    Q_INVOKABLE void setAuthorizationPageState(const int newAuthorizathionPageState);

    const QString &nickname() const;
    Q_INVOKABLE void setNickname(const QString &newNickname);

    const QString &password() const;
    Q_INVOKABLE void setPassword(const QString &newPassword);

    const QString &ethalonPassword() const;
    void setEthalonPassword(const QString &newEthalonPassword);

    int dimension() const;
    Q_INVOKABLE void setDimension(int newDimension);

    bool connectionState() const;
    void setConnectionState(bool newConnectionState);

    Q_INVOKABLE void addNewUser(const QString &nickname, const QString &password);

    Q_INVOKABLE void requestUserPassword(const QString& password);



signals:
    void noServerConnection();
    void authorizationPageStateChanged(int newAuthorizathionPageState);
    void nicknameChanged(const QString &nickname);
    void passwordChanged(const QString &password);
    void ethalonPasswordChanged(const QString &ethalonPassword);
    void dimensionChanged(int dimension);
    void connectionStateChanged(bool connectionState);
    void nicknameExistanceInternalServerError();
    void passwordInternalServerError();
    void userAdditionInternalServerError();
    void recordAdditionInternalServerError();
    void topTimeInternalServerError();
    void topTurnsInternalServerError();
    void nicknameExists();

private slots:
    void onConnectionStateChanged(net::ConnectionState state);
    void onInternalServerErrorOccured(net::InternalServerError error);
    void onUserAdded(bool additionResult);
    void onPasswordDownloaded(const QString &password);
    void onNicknameExists();

private:
    AuthorizationManager();    

    enum class AuthorizationPageState {
        NICKNAME_INPUT,
        PASSWORD_INPUT,
        DIMENSION_SELECTION
    };

    AuthorizationPageState m_authorizathionPageState;
    QString m_nickname;
    QString m_password;
    QString m_ethalonPassword;
    int m_dimension;
    bool m_connectToServer;

    NicknameHint m_nicknameHint;


};

#endif // AUTHORIZATIONMANAGER_H
