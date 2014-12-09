#include "noterequests.h"

NoteRequests::NoteRequests(QString url,QString userid)
{
    serverUrl=url;
    userId=userid;
}
NoteRequests::NoteRequests(QString url)
{
    serverUrl=url;

}
QList<Note> NoteRequests::getNotes(){

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
QString NoteRequests::createNote(QString sTitle,QString sBodytext){

    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QUrl serviceUrl =QUrl(serverUrl+"/createnote");

    QByteArray jsonString = QByteArray("{");
    jsonString.append("\"userid\":");
    jsonString.append("\"");
    jsonString.append(userId.toInt());
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
void NoteRequests::updateNote(Note note){
    QEventLoop eventLoop;
    // "quit()" the event-loop, when the network request "finished()"
    QUrl serviceUrl =QUrl(serverUrl+"/updatenote");

    QString userid=QString::number(note.getId());
    QString ownerid=QString::number(note.getOwner());
    QByteArray jsonString = QByteArray("{");
    jsonString.append("\"id\":");
    jsonString.append("\"");
    jsonString.append(userid);
    jsonString.append("\"");
    jsonString.append("\"userid\":");
    jsonString.append("\"");
    jsonString.append(ownerid);
    jsonString.append("\"");
    jsonString.append(",\"title\":");
    jsonString.append("\"");
    jsonString.append(note.getTitle());
    jsonString.append("\"");
    jsonString.append(",\"textbody\":");
    jsonString.append("\"");
    jsonString.append(note.getBody());
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
        //return "success";

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        //return reply->errorString();

    }
}
