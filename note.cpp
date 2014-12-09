#include "note.h"

Note::Note(int noteid, int ownerId, QString title, QString body)
{
    id=noteid;
    sTitle=title;
    sOwnerId=ownerId;
    sTextbody=body;
}
Note::Note(){

}

QString Note::getTitle()
{
    return sTitle;
}
QString Note::getBody()
{
    return sTextbody;
}
int Note::getId(){
    return id;
}
int Note::getOwner(){
    return sOwnerId;
}
