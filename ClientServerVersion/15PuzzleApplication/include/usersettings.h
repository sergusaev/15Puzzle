#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QSettings>

class UserSettings: public QObject
{
    Q_OBJECT
public:
     UserSettings(QObject *parent = nullptr);

    ~UserSettings();

    Q_INVOKABLE void writeSettings(const QString &nickname, const QString &password, int dimension, int authorizationPageState);

    Q_INVOKABLE QString readNickname();

    Q_INVOKABLE QString readPassword();

    Q_INVOKABLE int readDimension();

    Q_INVOKABLE int readAuthorizationPageState();

    Q_INVOKABLE void clearSettings();

private:   
     QSettings m_userSettings;
};

#endif // USERSETTINGS_H
