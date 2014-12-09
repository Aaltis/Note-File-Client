#include "userrequests.h"

UserRequests::UserRequests()
{
}
void UserRequests::createUser(QString sUserName,QString sPassword,QString sRepassword){
    // create custom temporary event loop on stack
    QEventLoop eventLoop;


    // "quit()" the event-loop, when the network request "finished()"
    QUrl serviceUrl =QUrl("http://127.0.0.1:5000/adduser");

    QByteArray jsonString = QByteArray("{");
    jsonString.append("\"emailaddress\":");
    jsonString.append("\"");
    jsonString.append(sUserName);
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
int UserRequests::login(QString sUserName,QString sPassword){
    // create custom temporary event loop on stack
    QEventLoop eventLoop;


    // "quit()" the event-loop, when the network request "finished()"

    QUrl url("http://127.0.0.1:5000/login?emailaddress=" + sUserName +"&password=" + sPassword);


    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = mgr.get(networkRequest);

    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Success" <<reply->readAll();

        QJsonParseError jerror;
        QJsonDocument jdoc= QJsonDocument::fromJson(reply->readAll(),&jerror);
        if(jerror.error != QJsonParseError::NoError)
        {
            return 0;
        }
        QJsonObject obj = jdoc.object();
        int userid = obj["userid"].toInt();
        return userid;

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return 0;
    }
}

