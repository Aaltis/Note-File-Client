#include "getnotesrequest.h"

GetnotesRequest::GetnotesRequest(QString userId)
{
    sUserId=userId;
}
QList<Note> GetnotesRequest::sendRequest(){

    // create custom temporary event loop on stack
    QEventLoop eventLoop;


    // "quit()" the event-loop, when the network request "finished()"

    QUrl url("http://127.0.0.1:5000/getnotes?userid=" + sUserId);
    QNetworkAccessManager mgr;

    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = mgr.get(networkRequest);
    QList <Note> notes;
    //eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObject = jsonResponse.object();

        QJsonArray jsonArray = jsonObject["notes"].toArray();

        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            Note note(obj["id"].toInt(),obj["ownerId"].toString(),obj["title"].toString(),obj["text"].toString());

            notes.append(note);
        }

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return notes;
    }
}
