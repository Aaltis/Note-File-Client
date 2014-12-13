#ifndef FILE_H
#define FILE_H
#include "qstring.h"
/*
 * Holder Class for file data to be shown in list.
 */
class File
{
public:
    File(int id,QString name);
    File();
    int getId();
    QString getName();
private:
    int iId;
    QString sName;
};

#endif // FILE_H
