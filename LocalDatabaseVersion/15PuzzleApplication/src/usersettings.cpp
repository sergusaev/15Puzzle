#include "usersettings.h"

UserSettings::UserSettings(QObject *parent)
{
    Q_UNUSED(parent)

}

UserSettings::~UserSettings() {

}

void UserSettings::writeSettings(const QString& nickname, const QString& password, int dimension)
{
    m_userSettings.setValue("nickname", nickname);
    m_userSettings.setValue("password", password);
    m_userSettings.setValue("dimension", dimension);
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



