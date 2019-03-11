#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public :
    bool isLogin() { return !user_id.isEmpty(); }

    QString user_id;
    QString username;
    QString password;
    QString nickname;

};

#endif // USER_H
