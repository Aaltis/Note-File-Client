#include "noterequests.h"

NoteRequests::NoteRequests(QString url)
{
    serverUrl=url;
}
NoteRequests::NoteRequests(QString url,QString uId)
{
    serverUrl=url;
    userId=uId;

}
QList<Note> NoteRequests::getNotes(QString userId){

    // create custom temporary event loop on stack


    // "quit()" the event-loop, when the network request "finished()"
    QString fullServerPath=serverUrl+"/getnotes?userid=";
    QUrl url(fullServerPath+userId);
    QNetworkAccessManager mgr;

    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QEventLoop eventLoop;

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));


    QNetworkReply *reply = mgr.get(networkRequest);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QList <Note> notes;
    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();
        QJsonParseError jerror;
        qDebug() << "Response:" << strReply;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObject = jsonResponse.object();

        QJsonArray jsonArray = jsonObject["notes"].toArray();

        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            Note note(obj["id"].toInt(),obj["ownerid"].toInt(),obj["title"].toString(),obj["text"].toString());
            notes.append(note);


        }
        return notes;


    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return notes;
    }
}
QString NoteRequests::getNote(QString id){

    // create custom temporary event loop on stack


    // "quit()" the event-loop, when the network request "finished()"
    QString fullServerPath=serverUrl+"/getnote?id=";
    QUrl url(fullServerPath+id);
    QNetworkAccessManager mgr;

    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QEventLoop eventLoop;

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));


    QNetworkReply *reply = mgr.get(networkRequest);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        QString strReply = (QString)reply->readAll();
        QJsonParseError jerror;
        qDebug() << "Response:" << strReply;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QString text = jsonObject["notetext"].toString();
        return text;


    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return 0;
    }
}
QString NoteRequests::createNote(QString sTitle,QString sBodytext){

    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QUrl serviceUrl =QUrl(serverUrl+"/createnote");

    QByteArray jsonString = QByteArray("{");
    jsonString.append("\"userid\":");
    jsonString.append("\"");
    jsonString.append(userId);
    jsonString.append("\"");
    jsonString.append(",\"title\":");
    jsonString.append("\"");
    jsonString.append(sTitle);
    jsonString.append("\"");
    jsonString.append(",\"textbody\":");
    jsonString.append("\"");
    jsonString.append(sBodytext);
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
void NoteRequests::updateNote(QString selected,QString ownerid,QString text){
    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QUrl serviceUrl =QUrl(serverUrl+"/updatenote");


    QByteArray jsonString = QByteArray("{");
    jsonString.append("\"id\":");
    jsonString.append("\"");
    jsonString.append(selected);
    jsonString.append("\"");
    jsonString.append(",\"userid\":");
    jsonString.append("\"");
    jsonString.append(ownerid);
    jsonString.append("\"");
    jsonString.append(",\"text\":");
    jsonString.append("\"");
    jsonString.append(text);
    jsonString.append("\"");
    jsonString.append("}");

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest networkRequest(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply * reply= mgr.put(networkRequest,jsonString);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        qDebug() << "Success" <<reply->readAll();

        delete reply;
        //return "success";

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        //return reply->errorString();

    }
}
