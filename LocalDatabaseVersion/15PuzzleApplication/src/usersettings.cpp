#include "usersettings.h"

UserSettings::UserSettings(QObject *parent)
    : m_userSettings ("Usaev Soft", "15PuzzleApplication")

{
    Q_UNUSED(parent)

}

UserSettings::~UserSettings() {

}

void UserSettings::writeSettings(const QString& nickname, const QString& password, int dimension)
{
    m_userSettings.beginGroup("AuthorizationWindow");
    m_userSettings.setValue("nickname", nickname);
    m_userSettings.setValue("password", password);
    m_userSettings.setValue("dimension", dimension);
    m_userSettings.endGroup();
}

QString UserSettings::readNickname()
{
    QString ret;
    m_userSettings.beginGroup("AuthorizationWindow");
    ret = m_userSettings.value("nickname").toString();
    m_userSettings.endGroup();
    return ret;
}
QString UserSettings::readPassword()
{
    QString ret;
    m_userSettings.beginGroup("AuthorizationWindow");
    ret = m_userSettings.value("password").toString();
    m_userSettings.endGroup();
    return ret;
}

int UserSettings::readDimension()
{
    int ret;
    m_userSettings.beginGroup("AuthorizationWindow");
    ret = m_userSettings.value("dimension").toInt();
    m_userSettings.endGroup();
    return ret;
}



