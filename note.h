#ifndef NOTE_H
#define NOTE_H
#include <qstring.h>
class Note
{
public:
    Note(int noteid,int ownerId,QString title,QString body);
    Note();
    int getId();
    int getOwner();
    QString getTitle();
    QString getBody();
private:
    int id;
    int sOwnerId;
    QString sTitle;
    QString sTextbody;
};

#endif // NOTE_H
