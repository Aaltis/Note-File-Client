#ifndef NEWUSERREQUEST_H
#define NEWUSERREQUEST_H
#include <QString>
class NewUserRequest
{
public:
     NewUserRequest(QString s_Username,QString s_Password,QString s_RePassword);
    ~NewUserRequest();
    void sendRequest();
private:
    NewUserRequest();
    QString sUsername;
    QString sPassword;
    QString sRepassword;
};

#endif // NEWUSERREQUEST_H
