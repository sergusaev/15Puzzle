#include "usersettings.h"

UserSettings::UserSettings(QObject *parent)
{
    Q_UNUSED(parent)

}

UserSettings::~UserSettings() {

}

void UserSettings::writeSettings(const QString& nickname, const QString& password, int dimension, int authorizationState)
{
    m_userSettings.setValue("nickname", nickname);
    m_userSettings.setValue("password", password);
    m_userSettings.setValue("dimension", dimension);
    m_userSettings.setValue("authorizationState", authorizationState);
}

QString UserSettings::readNickname()
{
    QString ret;
    ret = (!m_userSettings.value("nickname").isNull()) ? m_userSettings.value("nickname").toString() : "";
    return ret;
}

QString UserSettings::readPassword()
{
    QString ret;
    ret = (!m_userSettings.value("password").isNull()) ? m_userSettings.value("password").toString() : "";
    return ret;
}

int UserSettings::readDimension()
{
    int ret;
    ret = (!m_userSettings.value("dimension").isNull()) ? m_userSettings.value("dimension").toInt() : 2;
    return ret;
}

int UserSettings::readAuthorizationPageState()
{
    int ret;
    ret = (!m_userSettings.value("authorizationState").isNull()) ? m_userSettings.value("authorizationState").toInt() : 1;
    return ret;}

void UserSettings::clearSettings()
{
    m_userSettings.setValue("nickname", "");
    m_userSettings.setValue("password", "");
    m_userSettings.setValue("dimension", 2);
    m_userSettings.setValue("authorizationState", 1);
}



