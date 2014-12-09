#include "loginrequest.h"

LoginRequest::LoginRequest(QString mUsername, QString mPassword)
{
    m_username=mUsername;
    m_password=mPassword;
    //Signal comes, slot happens
    //QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
}

LoginRequest::~LoginRequest()
{

}
int LoginRequest::sendRequest(){

    // create custom temporary event loop on stack
    QEventLoop eventLoop;


    // "quit()" the event-loop, when the network request "finished()"

    QUrl url("http://127.0.0.1:5000/login?emailaddress=" + m_username +"&password=" + m_password);


    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = mgr.get(networkRequest);

    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {
        QString strReply = (QString)reply->readAll();

        QJsonParseError jerror;
        QJsonDocument jdoc= QJsonDocument::fromJson(reply->readAll(),&jerror);
        if(jerror.error != QJsonParseError::NoError)
        {
            return NULL;
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
void LoginRequest::parseNetworkResponse(QNetworkReply *finished){
    if ( finished->error() != QNetworkReply::NoError )
    {
        // A communication error has occurred
        qDebug() << "Failure" <<finished->errorString();
        QString data = finished->errorString();
        sendloginResult(data);
        //emit loginResult( data );
        //return data;
    }

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString data = finished->readAll();
    qDebug() << "Success" <<finished->readAll();

    emit sendloginResult(data);
    //emit loginResult( data );
}
