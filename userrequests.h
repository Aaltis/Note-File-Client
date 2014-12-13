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
class UserRequests : public QObject
{
Q_OBJECT  // Enable signals and slots
public:

    UserRequests(QString serverurl);
    ~UserRequests();
    void createUser(QString sUserName,QString sPassword,QString sRepassword);
    QString login(QString sUserName,QString sPassword);
    QString serverUrl;
signals:
    void querySuccess(QString message);
    void queryFailure(QString message);
private:
    QEventLoop* signalLoop;
    QNetworkAccessManager *manager;
    QNetworkReply* reply;
    QString parseReplyResult(QNetworkReply *reply);
    int parseLoginResult(QNetworkReply *reply);

};

#endif // USERREQUESTS_H
