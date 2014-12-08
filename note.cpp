#include "note.h"

Note::Note(int noteid,QString ownerId,QString title,QString body)
{
    id=noteid;
    sOwnerId=ownerId;
    sTitle=title;
    sTextbody=body;
}
