#include "filerequests.h"

FileRequests::FileRequests(QString url,QString userid)
{
    serverUrl=url;
    userId=userid;
}
FileRequests::~FileRequests(){

}

void FileRequests::startSend(QString absoluteFilepath){
    //https://stackoverflow.com/questions/23996444/post-file-upload-works-with-curl-but-not-with-qt-seafile-web-api
    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QFile *file = new QFile{absoluteFilepath};
    if (!file->exists()) {
        qDebug() << "Error occured: file not found";
        return;
    }
    QFileInfo fileInfo(absoluteFilepath);
    QString sFileName = fileInfo.fileName();

    QHttpPart file_part;
    file_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+ sFileName + "\""));
    file_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    multipart->append(file_part);

    QNetworkRequest req;
    req.setUrl(QUrl(serverUrl+"/filetransfersend?emailaddress="+userId)); //my virtual servers' ip address and tiny php page url is here
    req.setRawHeader("Content-Type", "multipart/form-data; boundary=" + multipart->boundary());
    manager = new QNetworkAccessManager;
    //multipart->setParent(pReply);
    reply=manager->post(req, multipart);
    signalLoop= new QEventLoop();
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(uploadProgress(qint64,qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()),this, SLOT(uploadFinished()));
    signalLoop->exec();
}
