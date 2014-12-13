#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H
#include "qstring.h"
#include <QApplication>
#include <QSettings>
#include <QString>
#include <QDir>
class SettingsHandler
{
public:
    SettingsHandler();
    QString loadServerUrl();
    void saveServerUrlRemote(QString url);
    void saveServerUrlLocal();
    void saveLoginData(QString name, QString password, QString userid);
    void loadLoginData();
    QString getLoginName();
    QString getPassword();
    QString getServerUrl();
    QString getUserID();
private:
    QString m_sSettingsFile;
    QString sLoginName;
    QString sPassword;
    QString sServerUrl;
    QString sUserId;


};

#endif // SETTINGSHANDLER_H
