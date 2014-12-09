#ifndef FILEREQUESTS_H
#define FILEREQUESTS_H

#include "qstring.h"
#include "qhttpmultipart.h"
#include "QNetworkReply"
#include "QNetworkAccessManager"
#include "qfile.h"
#include "qeventloop.h"
#include "qfileinfo.h"
class FileRequests: public QObject
{
   Q_OBJECT
public:
    FileRequests(QString url,QString userid);
    ~FileRequests();
    void startSend(QString absoluteFilepath);
    QNetworkReply *reply;
private:
    QString serverUrl;
    QString userId;
    QEventLoop* signalLoop;
    QNetworkAccessManager *manager;
};

#endif // FILEREQUESTS_H
