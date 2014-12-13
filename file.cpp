#include "file.h"

/*
 * Holder Class for file data to be shown in list.
 */
File::File(int id, QString name)
{
    iId=id;
    sName=name;
}
int File::getId(){
    return iId;
}
QString File::getName(){
    return sName;
}
