#include "usersettings.h"

UserSettings::UserSettings(QObject *parent)
    : m_userSettings ("Usaev Soft", "15PuzzleApplication")

{
    Q_UNUSED(parent)

}

UserSettings::~UserSettings() {

}

void UserSettings::writeSettings(const QString& nickname)
{
    m_userSettings.beginGroup("AuthorizationWindow");
    m_userSettings.setValue("nickname", nickname);
//    m_userSettings.setValue("dimension", dimension);
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

int UserSettings::readDimension()
{
    int ret;
    m_userSettings.beginGroup("AuthorizationWindow");
    ret = m_userSettings.value("nickname").toInt();
    m_userSettings.endGroup();
    return ret;
}

