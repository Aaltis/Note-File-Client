#include "settingshandler.h"
#include <QApplication>
#include <QSettings>
#include <QString>
/*
 * Handles setting ini file.
 */
SettingsHandler::SettingsHandler()
{
    QSettings settings("mySettings", QSettings::NativeFormat);
    sLoginName=settings.value("name", "").toString();
    sPassword= settings.value("password", "").toString();
    sServerUrl= settings.value("serverurl", "").toString();
    sUserId= settings.value("userid", "").toString();
}
QString SettingsHandler::loadServerUrl()
{
    QSettings settings("mySettings", QSettings::NativeFormat);
    QString sText = settings.value("serverurl", "").toString();
    return sText;
}
void SettingsHandler::saveServerUrlRemote(QString url)
{
    QSettings settings("mySettings", QSettings::NativeFormat);
    settings.setValue("serverurl", url);
    settings.sync();

}

void SettingsHandler::saveServerUrlLocal()
{
    QSettings settings("mySettings", QSettings::NativeFormat);
    settings.setValue("serverurl", "http://127.0.0.1:5000");
    settings.sync();

}
void SettingsHandler::saveLoginData(QString name,QString password,QString userid)
{
    QSettings settings("mySettings", QSettings::NativeFormat);
    settings.setValue("name", name);
    settings.setValue("password", password);
    settings.setValue("userid", userid);
    settings.sync();
}
void SettingsHandler::loadLoginData()
{
    QSettings settings("mySettings", QSettings::NativeFormat);
    sLoginName=settings.value("name", "").toString();
    sPassword= settings.value("password", "").toString();
}


QString SettingsHandler::getLoginName(){
    return sLoginName;
}
QString SettingsHandler::getPassword(){
    return sPassword;
}

QString SettingsHandler::getServerUrl(){
    return sServerUrl;
}
QString SettingsHandler::getUserID(){
    return sUserId;
}



