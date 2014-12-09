#ifndef FILESENDREQUEST_H
#define FILESENDREQUEST_H
#include <QtNetwork>

#include <QString>
#include <QHttpMultiPart>

class FileSendRequest: public QObject
{
   Q_OBJECT
public:
    FileSendRequest(QString surl, QString absoluteFilepath,QString userid);
    ~FileSendRequest();
    void startSend();
    QNetworkReply *reply;
private:
     QString absoluteFilepath;
     QString serverUrl;
     QString userId;
     QEventLoop* signalLoop;
     QNetworkAccessManager *manager;

private slots:
       void uploadFinished();
       void uploadProgress(qint64 a, qint64 b);
       void onError(QNetworkReply::NetworkError err);
};

#endif // FILESENDREQUEST_H
