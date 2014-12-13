#include "filerequests.h"
/*
 * Class to handle calls to backend for file upload, download and deletion.
 */

//initialisation in every request needs serverurl and userid
FileRequests::FileRequests(QString url,QString userid)
{
    serverUrl=url;
    userId=userid;
}
FileRequests::~FileRequests(){
}
/*
 * Funktion for filesend with httpmultipart post data.
 * Was hard to get work right.
 */
void FileRequests::startSend(QString absoluteFilepath){

    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QFile *file = new QFile{absoluteFilepath};
    if (!file->exists()) {
        qDebug() << "Error occured: file not found";
        return;
    }
    QFileInfo fileInfo(absoluteFilepath);
    QString sFileName = fileInfo.fileName();

    //Add headers
    QHttpPart file_part;
    file_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+ sFileName + "\""));
    file_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));

    //open file for send
    file->open(QIODevice::ReadOnly);
    file_part.setBodyDevice(file);
    file->setParent(multipart); // we cannot delete the file now, so delete it with the multipart

    multipart->append(file_part);


    QNetworkRequest req;
    QString fullUrl =serverUrl+"/filetransfersend?id="+userId;
    req.setUrl(QUrl(fullUrl));
    req.setRawHeader("Content-Type", "multipart/form-data; boundary=" + multipart->boundary());

    manager = new QNetworkAccessManager;

    reply=manager->post(req, multipart);
    signalLoop= new QEventLoop();

    //debug signals, was meant to be used for stylish upload bar for further developement
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()),this, SLOT(uploadFinished()));
    signalLoop->exec();

    if (reply->error() == QNetworkReply::NoError) {
        delete reply;
        //qDebug() << "Success" <<reply->readAll();
        emit fileSend("File "+sFileName+" Saved");

    }
    else {
        //failure
        QString message=parseReplyResult(reply);
        emit queryFailure(message);
        delete reply;
    }


}

/*
 * Funktion to sen delete request for backend.
 */

void FileRequests::deleteFile(QString fileName){

    QEventLoop eventLoop;

    QString fullUrl=serverUrl+"/filetransferdelete?filename=" + fileName +"&ownerid=" + userId;
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
        qDebug() << "Success" <<reply->readAll();
        emit fileDeleted(message);
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
 * Get list of users files
 */
QList<File> FileRequests::getFilesList(QString userId){
    QString fullServerPath=serverUrl+"/getfilelist?userid=";
    QUrl url(fullServerPath+userId);
    QNetworkAccessManager mgr;

    // the HTTP request

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QEventLoop eventLoop;

    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));


    QNetworkReply *reply = mgr.get(networkRequest);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    QList <File> files;
    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();
        QJsonParseError jerror;
        qDebug() << "Response:" << strReply;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObject = jsonResponse.object();

        QJsonArray jsonArray = jsonObject["files"].toArray();

        foreach (const QJsonValue & value, jsonArray)
        {
            QJsonObject obj = value.toObject();
            File file(obj["id"].toInt(),obj["name"].toString());
            files.append(file);

        }
        return files;

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;

    }
}

/*
 * Funktion for file download purposes.
 */
void FileRequests::getFile(QString userId,QString fileName){
    QString fullQuery=serverUrl+"/filetransferget?userid="+userId+"&filename=" + fileName;
    QUrl url(fullQuery);
    QNetworkAccessManager mgr;


    // the HTTP request
    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    signalLoop= new QEventLoop();
    QNetworkReply *reply = mgr.get(networkRequest);

    //QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &signalLoop, SLOT(quit()));

    connect(&mgr, SIGNAL(finished(QNetworkReply*)), signalLoop , SLOT(quit()));

    signalLoop->exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Response:" << "we got file!";
        QByteArray data = reply->readAll();
        QFile *dataFile = new QFile(fileName);
        dataFile->open(QIODevice::WriteOnly | QIODevice::Text);
        dataFile->write(data);
        dataFile->flush();
        dataFile->close();
    }
}
void FileRequests::uploadFinished()
{
    QString data = (QString) reply->readAll();
    qDebug() << data;
    qDebug() << "Upload finished";

    //uploadInProgress = false;
    if ( reply->error() > 0 )
    {
        qDebug() << "Error occured: " << reply->error() << " : " << reply->errorString();
    }
    else
    {
        qDebug() << "Upload success";
    }
    reply->deleteLater();
    signalLoop->exit();
}

void FileRequests::uploadProgress(qint64 a, qint64 b)
{
    qDebug() << " SOME PROGRESS!";
    qDebug() << a  << "/" << b;
}

void FileRequests::onError(QNetworkReply::NetworkError err)
{
    qDebug() << " SOME ERROR!";
    qDebug() << err;
}

QString FileRequests::parseReplyResult(QNetworkReply *reply){

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



