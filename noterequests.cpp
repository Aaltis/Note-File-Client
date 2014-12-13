#include "noterequests.h"
/*
 * Class to handle calls to backend for note upload, download and deletion.
 */

//initialisation in every request needs serverurl and userid
NoteRequests::NoteRequests(QString url)
{
    serverUrl=url;
}
NoteRequests::NoteRequests(QString url,QString uId)
{
    serverUrl=url;
    userId=uId;

}
/*
 * Get list of notes from backend and store them to note objects
 */
QList<Note> NoteRequests::getNotes(QString userId){


    QString fullServerPath=serverUrl+"/getnotes?userid="+userId;
    QUrl url(fullServerPath);
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

        //build note list
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

/*
 * send json post to create note to database.
 */
QString NoteRequests::createNote(QString sTitle,QString sBodytext){

    QEventLoop eventLoop;
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
    QNetworkRequest networkRequest(serviceUrl);

    //headers
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply * reply= mgr.post(networkRequest,jsonString);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        QString message=parseReplyResult(reply);
        //success
        qDebug() << "Success" <<message;
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
 * Update notes text.
 */
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
        QString message=parseReplyResult(reply);
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
void NoteRequests::deleteNote(QString selected,QString ownerid){

    QEventLoop eventLoop;
    QString fullUrl=serverUrl+"/deletenote?noteid=" + selected +"&ownerid=" + ownerid;
    QUrl serviceurl(fullUrl);
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest networkRequest(serviceurl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply * reply= mgr.deleteResource(networkRequest);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        QString message=parseReplyResult(reply);
        //success
        qDebug() << "Success" <<reply->readAll();
        emit noteDeleted();
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
 * Parse json reply
 */
QString NoteRequests::parseReplyResult(QNetworkReply *reply){

    QJsonParseError jerror;
    QJsonDocument jdoc= QJsonDocument::fromJson(reply->readAll(),&jerror);
    if(jerror.error != QJsonParseError::NoError)
    {
        //     return 0;
    }
    QJsonObject obj = jdoc.object();
    QString result = obj["result"].toString();
    return result;
}



