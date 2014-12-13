#include "userrequests.h"

/*
 * initialisation in every request needs serverurl and userid
 */

UserRequests::UserRequests(QString serverurl)
{
    serverUrl=serverurl;
}

UserRequests::~UserRequests(){

}
/*
 * Funktion handles json post for backend for user creation
 */
void UserRequests::createUser(QString sUserName,QString sPassword,QString sRepassword){
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    QUrl serviceUrl =QUrl(serverUrl+"/adduser");

    //build jsonstring for send
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

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = mgr.post(networkRequest,jsonString);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        QString message=QString::number(parseLoginResult(reply));
        //success
        qDebug() << "Success" <<reply->readAll();
        emit querySuccess(message);
        delete reply;

    }
    else {
        //failure
        QString message=parseReplyResult(reply);
        emit queryFailure(message);
        delete reply;
    }
}
/*
 * Funktion handles json get for backend for user creation
 */
QString UserRequests::login(QString sUserName,QString sPassword){
    // create custom temporary event loop on stack
    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QUrl url(serverUrl+"/login?emailaddress=" + sUserName +"&password=" + sPassword);


    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = mgr.get(networkRequest);

    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        QString message=QString::number(parseLoginResult(reply));
        //success
        qDebug() << "Success" <<reply->readAll();
        return message;
        delete reply;

    }
    else {
        //failure
        QString message=parseReplyResult(reply);
        //emit queryFailure(message);
        return message;
        delete reply;
    }
}
/*
 * Parse regural text json results for furter useage
 */
QString UserRequests::parseReplyResult(QNetworkReply *reply){

    QJsonParseError jerror;
    QJsonDocument jdoc= QJsonDocument::fromJson(reply->readAll(),&jerror);
    if(jerror.error != QJsonParseError::NoError)
    {
        return 0;
    }
    QJsonObject obj = jdoc.object();
    QString result = obj["result"].toString();
    return result;
}
/*
 * Parse regural login result because its int.
 */
int UserRequests::parseLoginResult(QNetworkReply *reply){

    QJsonParseError jerror;
    QJsonDocument jdoc= QJsonDocument::fromJson(reply->readAll(),&jerror);
    if(jerror.error != QJsonParseError::NoError)
    {
        return 0;
    }
    QJsonObject obj = jdoc.object();
    int result = obj["result"].toInt();
    return result;
}



