#ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H

#include "storage.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>

#include "passhash.h"

class SqliteStorage : public Storage
{
  const string dir_name_;
  QSqlDatabase db_;

public:
  SqliteStorage(const string & dir_name);

  bool open();
  bool close();
  // dinosaurs
  vector<Dino> getAllDinos(void);
  optional<Dino> getDinoById(int Dino_id);
  bool updateDino(const Dino &dvno);
  bool removeDino(int Dino_id);
  int insertDino(const Dino &dvno);


  // periods
  vector<Per> getAllPers(void);
  optional<Per> getPerById(int Per_id);
  bool updatePer(const Per &pr);
  bool removePer(int Per_id);
  int insertPer(const Per &pr);

  vector<Dino> getAllUserDino(int user_id);

  optional<User> getUserAuth(string & username, string & password);

  vector<Per> getAllDinoPer(int dino_id);
  bool insertDinoPer(int dino_id, int per_id);
  bool removeDinoPer(int dino_id, int per_id);

  vector<Dino> getAllUserDino2(int user_id, QString & par, QString & ord);

  vector<Per> getAllNotDinoPer(int dino_id);
  vector<Dino> getFreeDinos();

  vector<Dino> getAllUserDinoPage(int user_id, int page);

  vector<Dino> getAllUserDinoPageSearch(int user_id, int page, QString & search);

  vector<Dino> getAllUserDinoSearch(int user_id, QString & string);

  vector<Per> getAllDinoPerSearch(int dino_id, QString & search);

  vector<Per> getAllDinoPerPage(int dino_id, int page);

  int insertNewUser(const QString & name, const QString & pass, QByteArray & pfp);

  User getUserById(int id);

  bool updatePfp(int id, QByteArray & pic);

  int namechange(QString & newname, QString & passhash, int uid);

  int passchange(QString & npasshash, QString & opasshash, int uid);



};

#endif // SQLITE_STORAGE_H
