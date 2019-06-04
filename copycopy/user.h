#pragma once

#include <string>
#include <QMetaType>
#include <QPixmap>

using namespace std;
struct  User
{
    int id = 0;
    string username = "";
    string password_hash = "";
    QPixmap pfp = QPixmap();

    User();
    User(int id, string username, string password_hash, QPixmap pfp);
};
Q_DECLARE_METATYPE(User)

