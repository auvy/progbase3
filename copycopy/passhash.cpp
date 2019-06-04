#include "passhash.h"


QString hashPassword(QString const & pass)
{
   QByteArray pass_ba = pass.toUtf8();
   QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
   QString pass_hash = QString(hash_ba.toHex());
   return pass_hash;
}


