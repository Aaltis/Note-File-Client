#include "filesendrequest.h"

FileSendRequest::FileSendRequest(QString surl, QString filepath,QString userid)
{
    absoluteFilepath=filepath;
    serverUrl =surl;
    userId=userid;
}
FileSendRequest::~FileSendRequest()
{


}
//https://stackoverflow.com/questions/18928545/qhttpmultipart-send-post-request-results-in-1
void FileSendRequest::startSend(){
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

    /*QHttpPart user_part;
    parent_dir_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    parent_dir_part.setBody("user");

    //user_part.setHeader(QNetworkRequest::);
    file->open(QIODevice::ReadOnly);
    file_part.setBodyDevice(file);
    file->setParent(multipart); // we cannot delete the file now, so delete it with the multipart

    /*QHttpPart parent_dir_part;
    parent_dir_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"parent_dir\""));
    parent_dir_part.setBody("/");
    */
    multipart->append(file_part);
   //  multipart->append(user_part);
    //multipart->append(parent_dir_part);

    QNetworkRequest req;
    req.setUrl(QUrl("http://127.0.0.1:5000/filetransfersend?emailaddress="+userId)); //my virtual servers' ip address and tiny php page url is here
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
void FileSendRequest::uploadFinished()
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

void FileSendRequest::uploadProgress(qint64 a, qint64 b)
{
    qDebug() << " SOME PROGRESS!";
    qDebug() << a  << "/" << b;
}

void FileSendRequest::onError(QNetworkReply::NetworkError err)
{
    qDebug() << " SOME ERROR!";
    qDebug() << err;
}
//http://www.qtcentre.org/threads/40734-Upload-file-to-HTTP-server
/*QFile file("/home/aaltis/x.txt"); //lets get the file by filename
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //accessibility controll for file
   {
   qDebug() << "file open failure"; //send message if file cant open
   }
   QByteArray line; //a qbytearray object for read file line by line
   while (!file.atEnd())
   {
   line.append(file.readLine());
   }
   //we read file line by line with no error handling for reading time!!

   file.close();
   QByteArray boundary; //actually i cant understand that why we are using a second byte array for file sending.
   // if someone know this trick please write below. I write this code like the other examples.

   QByteArray datas(("--" + boundary + "\r\n"));
   datas += "Content-Disposition: form-data; name=\"file\"; filename=\""+file.fileName()+"\"\r\n";
   //here is the http header for manuplate a normal http form and form file object

   datas += "Content-Type: image/jpeg\r\n\r\n"; //file type is here
   datas += line; //and our file is giving to form object
   datas += "\r\n";
   datas += QString("--" + boundary + "\r\n\r\n");
   datas += "Content-Disposition: form-data; name=\"upload\"\r\n\r\n";
   datas += "Uploader\r\n";
   datas += QString("--" + boundary + "--\r\n");

   QNetworkRequest req;
   req.setUrl(QUrl("http://127.0.0.1:5000/filetransfersend")); //my virtual servers' ip address and tiny php page url is here
   req.setRawHeader("Content-Type", "multipart/form-data; boundary=" + boundary); // we must set the first header like this. its tell the server, current object is a form

   QNetworkAccessManager *manager = new QNetworkAccessManager; //using qnetwork access manager for post data

   connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(erroron_filesend(QNetworkReply*))); //connecting manager object for errors here
   manager->post(req,datas); //send all data

   }
   /* QFile file("/home/aaltis/x.txt"); //lets get the file by filename
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //accessibility controll for file
   {
   qDebug() << "file open failure"; //send message if file cant open
   }
   QByteArray line; //a qbytearray object for read file line by line
   while (!file.atEnd())
   {
   line.append(file.readLine());
   }
   //we read file line by line with no error handling for reading time!!

   file.close();
   QByteArray boundary; //actually i cant understand that why we are using a second byte array for file sending.
   // if someone know this trick please write below. I write this code like the other examples.

   QByteArray datas("--" + boundary + "\r\n");
   datas += "Content-Disposition: form-data; name=\"file\"; filename=\""+file.fileName()+"\"\r\n";
   //here is the http header for manuplate a normal http form and form file object

   datas += "Content-Type: txt\r\n\r\n"; //file type is here
   datas += line; //and our file is giving to form object
   datas += "\r\n";
   datas += QString("--" + boundary + "\r\n\r\n");
   datas += "Content-Disposition: form-data; name=\"filetransfersend\r\n\r\n";
   datas += "Uploader\r\n";
   datas += QString("--" + boundary + "--\r\n");

   QNetworkRequest req;
  req.setUrl(QUrl("http://127.0.0.1:5000/filetransfersend")); //my virtual servers' ip address and tiny php page url is here
   req.setRawHeader("Content-Type", "multipart/form-data; boundary=" + boundary); // we must set the first header like this. its tell the server, current object is a form

   QNetworkAccessManager *manager = new QNetworkAccessManager; //using qnetwork access manager for post data

   connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(erroron_filesend(QNetworkReply*))); //connecting manager object for errors here
   manager->post(req,datas); //send all data
    //connect the reply object so we can track the progress of the upload
    /*QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);


    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("zip"));

    QFile *file = new QFile(absoluteFilepath);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart


    multiPart->append(imagePart);

    QUrl url("http://127.0.0.1:80/upload");
    QNetworkRequest request(url);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
   /* qDebug() << "Upload Starting";
    QFileInfo fileInfo(absoluteFilepath);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //action part
    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"preview_path"));
    textPart.setBody(QString(absoluteFilepath).toLatin1());

    //File Path
    QHttpPart filePathPart;
    filePathPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file_path\""));
    filePathPart.setBody(absoluteFilepath.toLatin1());

    QFile *file = new QFile(absoluteFilepath);
    if ( !file->exists() )
    {
        qDebug() << "File Does not exist";
    }
    //filepart
    QHttpPart filePart;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(absoluteFilepath);
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mime.name()));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"preview_file\"; filename=\""+ fileInfo.baseName() + "\""));



    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(textPart);
    multiPart->append(filePathPart);
    multiPart->append(filePart);

    QUrl url(serverUrl+"/filetransfersend");
    QNetworkRequest request(url);


    pManager = new QNetworkAccessManager();

    pReply = pManager->post(request, multiPart);
    multiPart->setParent(pReply);

    if (pReply->error() == QNetworkReply::NoError) {
        //success
        qDebug() << "Success" <<pReply->readAll();
        delete pReply;

    }


    else {
        //failure
        qDebug() << "Failure" <<pReply->errorString();
        delete pReply;
    }
*/




