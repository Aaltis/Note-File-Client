#ifndef NOTE_H
#define NOTE_H
#include <qstring.h>
class Note
{
public:
    Note(int noteid,QString ownerId,QString title,QString body);
    QString getTitle();
    QString getBody();
private:
    int id;
    QString sOwnerId;
    QString sTitle;
    QString sTextbody;
};

#endif // NOTE_H
