#ifndef LOGINREQUEST_H
#define LOGINREQUEST_H
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QEventLoop>
#include <QJsonObject>
class LoginRequest: public QObject

{
Q_OBJECT
public:
    LoginRequest(QString mUsername, QString mPassword);
   ~LoginRequest();

   int sendRequest();

private:
   LoginRequest();
   QString m_username;
   QString m_password;
   QNetworkAccessManager mgr;
signals:
    //void jsonResult( const QByteArray &result );
    //void networkError( QNetworkReply::NetworkError err);
     void sendloginResult(QString data);
     void loginResult(QString data);
public slots:
    void parseNetworkResponse( QNetworkReply *finished );
};
#endif // LOGINREQUEST_H
