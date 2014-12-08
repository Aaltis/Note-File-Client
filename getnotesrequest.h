#ifndef GETNOTESREQUEST_H
#define GETNOTESREQUEST_H
#include <QString>
#include <QStringList>
#include "note.h"
#include "qeventloop.h"
#include "qurl.h"
#include "qnetworkrequest.h"
#include <QNetworkAccessManager>
#include <qnetworkreply.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
class GetnotesRequest
{
public:
    GetnotesRequest(QString userId);
    QList<Note> sendRequest();
private:
    QString sUserId;
};

#endif // GETNOTESREQUEST_H
