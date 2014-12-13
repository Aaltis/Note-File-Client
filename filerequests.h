#ifndef FILEREQUESTS_H
#define FILEREQUESTS_H

#include "qstring.h"
#include "qhttpmultipart.h"
#include "QNetworkReply"
#include "QNetworkAccessManager"
#include "qfile.h"
#include "qeventloop.h"
#include "qfileinfo.h"
#include "file.h"
#include "qlist.h"
#include "QJsonParseError"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "qdir.h"
/*
 * Class to handle calls to backend for file upload, download and deletion.
 */
class FileRequests: public QObject
{
    Q_OBJECT
public:
    FileRequests(QString url,QString userid);
    ~FileRequests();
    void startSend(QString absoluteFilepath);
    QList<File> getFilesList(QString userId);
    QNetworkReply *reply;
    void getFilesList();
    void getFile(QString userId, QString fileName);
    void deleteFile(QString fileName);
private:
    QString serverUrl;
    QString userId;
    QString parseReplyResult(QNetworkReply *reply);

    QEventLoop* signalLoop;
    QNetworkAccessManager *manager;
    QFile *file;

private slots:
    void uploadFinished();
    void uploadProgress(qint64 a, qint64 b);
    void onError(QNetworkReply::NetworkError err);
signals:
    void fileDeleted(QString message);
    void fileSend(QString message);
    void queryFailure(QString message);

};

#endif // FILEREQUESTS_H
