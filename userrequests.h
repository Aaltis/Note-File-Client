#ifndef USERREQUESTS_H
#define USERREQUESTS_H
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include "QJsonParseError"
#include <QJsonObject>
class UserRequests
{
public:
    UserRequests();
    void createUser(QString sUserName,QString sPassword,QString sRepassword);
    int login(QString sUserName,QString sPassword);
};

#endif // USERREQUESTS_H
