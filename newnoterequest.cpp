#include "newnoterequest.h"

NewNoteRequest::NewNoteRequest(QString userId,QString title,QString textbody)
{
    sUserId=userId;
    sTitle=title;
    sTextBody=textbody;

}


QString NewNoteRequest::SendRequest(){

    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QUrl serviceUrl =QUrl("http://127.0.0.1:5000/createnote");

    QByteArray jsonString = QByteArray("{");
    jsonString.append("\"userid\":");
    jsonString.append("\"");
    jsonString.append(sUserId);
    jsonString.append("\"");
    jsonString.append(",\"title\":");
    jsonString.append("\"");
    jsonString.append(sTitle);
    jsonString.append("\"");
    jsonString.append(",\"textbody\":");
    jsonString.append("\"");
    jsonString.append(sTextBody);
    jsonString.append("\"");
    jsonString.append("}");


    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply * reply= mgr.post(networkRequest,jsonString);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        qDebug() << "Success" <<reply->readAll();

        delete reply;
        return "success";

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return reply->errorString();
    }
}

