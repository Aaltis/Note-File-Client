#include "newuserrequest.h"
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

NewUserRequest::NewUserRequest(QString s_Username,QString s_Password,QString s_RePassword)
{
    sUsername=s_Username;
    sPassword=s_Password;
    sRepassword=s_RePassword;
}

NewUserRequest::~NewUserRequest()
{

}
void NewUserRequest::sendRequest(){

       // create custom temporary event loop on stack
       QEventLoop eventLoop;


       // "quit()" the event-loop, when the network request "finished()"
       QUrl serviceUrl =QUrl("http://127.0.0.1:5000/adduser");

       QByteArray jsonString = QByteArray("{");
       jsonString.append("\"emailaddress\":");
       jsonString.append("\"");
       jsonString.append(sUsername);
       jsonString.append("\"");
       jsonString.append(",\"password\":");
       jsonString.append("\"");
       jsonString.append(sPassword);
       jsonString.append("\"");
       jsonString.append(",\"repassword\":");
       jsonString.append("\"");
       jsonString.append(sRepassword);
       jsonString.append("\"");
       jsonString.append("}");

       /*QByteArray jsonString = QByteArray("{");
       jsonString.append("\"emailaddress\":");
       jsonString.append("\"username@domain.com\"");
       jsonString.append(",\"password\":");
       jsonString.append("\"mypass\"");
       jsonString.append("}");*/

       //postData = params.toEncoded(QUrl::RemoveFragment);
   /*QByteArray postData;
       QUrl params;
       QUrlQuery query;
       query.addQueryItem("emailaddress", "string1");
       query.addQueryItem("password", "string2");

       params.setQuery(query);

       postData = params.toEncoded(QUrl::RemoveFragment);*/

          /*QUrl params;
          QUrlQuery query;
          query.addQueryItem("emailaddress","aaa");
          query.addQueryItem("password","ddd");

          params.setQuery(query);
          postData = params.toEncoded();*/
       QNetworkAccessManager mgr;
       QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

       // the HTTP request
       QNetworkRequest networkRequest(serviceUrl);
       networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
       QNetworkReply *reply = mgr.post(networkRequest,jsonString);
       eventLoop.exec(); // blocks stack until "finished()" has been called

       if (reply->error() == QNetworkReply::NoError) {
           //success
           qDebug() << "Success" <<reply->readAll();
           delete reply;

       }
       else {
           //failure
           qDebug() << "Failure" <<reply->errorString();
           delete reply;
       }
   }

