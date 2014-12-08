#ifndef NEWNOTEREQUEST_H
#define NEWNOTEREQUEST_H
#include <qstring.h>
#include <qeventloop.h>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
class NewNoteRequest
{
public:
    NewNoteRequest(QString userId, QString headline, QString textbody);
    QString SendRequest();
private:
    QString sTitle;
    QString sTextBody;
    QString sUserId;

};

#endif // NEWNOTEREQUEST_H
