#include "user.h"
#include <QDebug>

User::User() { }

User::User(int id, string username, string password_hash, QPixmap pfp)
{
    this->id = id;
    this->username =username;
    this->password_hash = password_hash;
    this->pfp = pfp;

}
