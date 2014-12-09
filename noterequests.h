#ifndef NOTEREQUESTS_H
#define NOTEREQUESTS_H
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

class NoteRequests
{
public:
    NoteRequests(QString url);
    NoteRequests(QString url,QString uId);
    QString createNote(QString sTitle,QString sBodytext);
    void updateNote(QString selected, QString ownerid, QString text);
    QList<Note>  getNotes(QString userId);
    QString getNote(QString id);
private:
    QString serverUrl;
    QString userId;
};

#endif // NOTEREQUESTS_H
