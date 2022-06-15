#ifndef AUTHORIZATIONMANAGER_H
#define AUTHORIZATIONMANAGER_H

#include <QObject>
#include "cachehandler.h"
#include "errorhandler.h"
#include <QtQml>
#include "requestshandlerclient.h"


class AuthorizationManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString ethalonPassword READ ethalonPassword WRITE setEthalonPassword NOTIFY ethalonPasswordChanged)
    Q_PROPERTY(int dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(bool connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)

public:
    static AuthorizationManager *instance();
    ~AuthorizationManager();

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
    void nicknameChanged(const QString &nickname);
    void passwordChanged(const QString &password);
    void ethalonPasswordChanged(const QString &ethalonPassword);
    void dimensionChanged(int dimension);
    void connectionStateChanged(bool connectionState);

private slots:
    void onConnectionStateChanged(net::ConnectionState state);
    void onUserAdded(bool additionResult);
    void onPasswordDownloaded(const QString &password);

private:
    AuthorizationManager();

    QString m_nickname;
    QString m_password;
    QString m_ethalonPassword;
    int m_dimension;
    bool m_connectionState;


};

#endif // AUTHORIZATIONMANAGER_H
