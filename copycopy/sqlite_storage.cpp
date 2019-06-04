#include "sqlite_storage.h"

#include <QtSql>

#include <QCryptographicHash>
#include <QDebug>

SqliteStorage::SqliteStorage(const string & dir_name) : dir_name_(dir_name)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
}


bool SqliteStorage::open()
{
    QString path = QString::fromStdString(this->dir_name_) + "/data.sqlite";

    db_.setDatabaseName(path);    // set sqlite database file path

    bool connected = db_.open();  // open db connection

    if (!connected) {return false;}
    return true;
}

bool SqliteStorage::close()
{
    db_.close();
    return true;
}


Dino getDinoFromQuery(const QSqlQuery & query)
{
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
//    string period = query.value("period").toString().toStdString();
    string family = query.value("family").toString().toStdString();
    int discovered = query.value("discovered").toInt();
    double mass = query.value("mass").toDouble();

    Dino d;
    d.id = id;
    d.name = name;
//    d.per = period;
    d.fam = family;
    d.disc = discovered;
    d.mass = mass;

    return d;
}

void queryBindDino(const Dino &dvno, QSqlQuery & query)
{
    query.bindValue(":name", QString::fromStdString(dvno.name));
//    query.bindValue(":period", QString::fromStdString(dvno.per));
    query.bindValue(":family", QString::fromStdString(dvno.fam));
    query.bindValue(":discovered", dvno.disc);
    query.bindValue(":mass", dvno.mass);
    query.bindValue(":user_id", dvno.user_id);
}

vector<Dino> SqliteStorage::getAllDinos(void)
{
    vector<Dino> dinos;
    QSqlQuery query("SELECT * FROM dinosaurs");
    while (query.next())
    {
       Dino d = getDinoFromQuery(query);
       dinos.push_back(d);
    }
    return dinos;
}

optional<Dino> SqliteStorage::getDinoById(int Dino_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE id = :id");
    query.bindValue(":id", Dino_id);

    if (!query.exec())
    {
       qDebug() << "get dinosaur error:" << query.lastError();
       return nullopt;
    }
    if (query.next())
    {
        Dino d = getDinoFromQuery(query);
        return d;
   }
    else {return nullopt;}

}

bool SqliteStorage::updateDino(const Dino &dvno)
{
    QSqlQuery query;
    query.prepare("UPDATE dinosaurs SET name = :name, family = :family, discovered = :discovered, mass = :mass WHERE id = :id");
    query.bindValue(":id", dvno.id);
    queryBindDino(dvno, query);

    if (!query.exec())
    {
        qDebug() << "updateDino error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

bool SqliteStorage::removeDino(int Dino_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM dinosaurs WHERE id = :id");
    query.bindValue(":id", Dino_id);

    if (!query.exec())
    {
        qDebug() << "deleteDino error: " << query.lastError();
        return false;
    }

    if(query.numRowsAffected() == 0) {return false;}

    return true;

}

int SqliteStorage::insertDino(const Dino &dvno)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dinosaurs (name, family, discovered, mass, user_id) VALUES (:name, :family, :discovered, :mass, :user_id)");

    queryBindDino(dvno, query);

    if (!query.exec())
    {
        qDebug() << "adddino error:" << query.lastError();
        return 0;
    }

    QVariant var = query.lastInsertId();
    return var.toInt();
}






Per getPerFromQuery(const QSqlQuery & query)
{
    int id = query.value("id").toInt();
    string name = query.value("name").toString().toStdString();
    double time = query.value("time").toDouble();

    Per p;
    p.id = id;
    p.name = name;
    p.time = time;

    return p;
}

void queryBindDino(const Per &pr, QSqlQuery & query)
{
    query.bindValue(":name", QString::fromStdString(pr.name));
    query.bindValue(":time", pr.time);
}

vector<Per> SqliteStorage::getAllPers(void)
{
    vector<Per> pers;
    QSqlQuery query("SELECT * FROM periods");
    while (query.next())
    {
       Per p = getPerFromQuery(query);
       pers.push_back(p);
    }
    return pers;
}

optional<Per> SqliteStorage::getPerById(int Per_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM periods WHERE id = :id");
    query.bindValue(":id", Per_id);

    if (!query.exec())
    {
       qDebug() << "get period error:" << query.lastError();
       return nullopt;
    }
    if (query.next())
    {
        Per p = getPerFromQuery(query);
        return p;
    }
    else return nullopt;
}

bool SqliteStorage::updatePer(const Per &pr)
{
    QSqlQuery query;
    query.prepare("UPDATE periods SET name = :name, time = :time WHERE id = :id");
    query.bindValue(":id", pr.id);
    queryBindDino(pr, query);

    if (!query.exec())
    {
        qDebug() << "updatePer error:" << query.lastError();
        return false;
    }
    if(query.numRowsAffected() == 0)
    {
        return false;
    }
    return true;
}

bool SqliteStorage::removePer(int Per_id)
{

    QSqlQuery query;
        query.prepare("DELETE FROM links WHERE id = :id");
        query.bindValue(":id", Per_id);

        if (!query.exec())
        {
            qDebug() << "deletePer error: " << query.lastError();
            return false;
        }

        if(query.numRowsAffected() == 0) {return false;}

        return true;



//    QSqlQuery query;
//    query.prepare("DELETE FROM periods WHERE id = :id");
//    query.bindValue(":id", Per_id);

//    if (!query.exec())
//    {
//        qDebug() << "deletePer error: " << query.lastError();
//        return false;
//    }

//    if(query.numRowsAffected() == 0) {return false;}

//    return true;

}

int SqliteStorage::insertPer(const Per &pr)
{
    QSqlQuery query;
    query.prepare("INSERT INTO periods (name, time) VALUES (:name, :time)");

    queryBindDino(pr, query);

    if (!query.exec())
    {
        qDebug() << "addPeriod error:" << query.lastError();
        return 0;
    }

    QVariant var = query.lastInsertId();
    return var.toInt();
}





vector<Dino> SqliteStorage::getAllUserDino(int user_id)
{
    vector<Dino> dinos;
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
        Dino d = getDinoFromQuery(query);
        dinos.push_back(d);

    }
    return dinos;
}


vector<Dino> SqliteStorage::getAllUserDinoSearch(int user_id, QString & string)
{
    QString s = "%" + string + "%";

    vector<Dino> dinos;
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id AND name || family LIKE :search");
    query.bindValue(":user_id", user_id);
    query.bindValue(":search", s);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
        Dino d = getDinoFromQuery(query);
        dinos.push_back(d);

    }
    return dinos;
}

vector<Dino> SqliteStorage::getAllUserDinoPage(int user_id, int page)
{
    int offset = 6 * (page - 1);

    vector<Dino> dinos;
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id LIMIT 6 OFFSET :offset");
    query.bindValue(":user_id", user_id);
    query.bindValue(":offset", offset);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
        Dino d = getDinoFromQuery(query);
        dinos.push_back(d);

    }
    return dinos;
}

vector<Dino> SqliteStorage::getAllUserDinoPageSearch(int user_id, int page, QString & search)
{
    int offset = 6 * (page - 1);

    QString s = "%" + search + "%";


    vector<Dino> dinos;
    QSqlQuery query;
    query.prepare("SELECT * FROM dinosaurs WHERE (user_id = :user_id) AND (name || family || discovered || mass LIKE :search ) LIMIT 6 OFFSET :offset");
    query.bindValue(":user_id", user_id);
    query.bindValue(":search", s);
    query.bindValue(":offset", offset);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
        Dino d = getDinoFromQuery(query);
        dinos.push_back(d);

    }
    return dinos;
}






vector<Dino> SqliteStorage::getAllUserDino2(int user_id, QString & par, QString & ord)
{
    vector<Dino> dinos;
    QSqlQuery query;
    if(par == "DEFAULT")
    {
        //NO SORTING
        query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id");
        query.bindValue(":user_id", user_id);
    }

    else if(par != "DEFAULT")
    {
        //SORTING BY COLUMNS AND ASCEND/DESCEND
        query.prepare("SELECT * FROM dinosaurs WHERE user_id = :user_id ORDER BY :PAR :ORD");
        query.bindValue(":user_id", user_id);
        query.bindValue(":PAR", par);
        query.bindValue(":ORD", ord);
    }

    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
        Dino d = getDinoFromQuery(query);
        dinos.push_back(d);

    }

    return dinos;
}



optional<User> SqliteStorage::getUserAuth(string & username, string & password)
{
    User user;
    QString fhash = hashPassword(QString::fromUtf8(password.c_str()));
    string passhash = fhash.toUtf8().constData();

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :un;");
    query.bindValue(":un", username.c_str());

    if(!query.exec())
    {
        qDebug() << "Unknown error: " << query.lastError();
        return nullopt;
    }

    if(query.next())
    {

            //if found user
            string uhash = query.value("password_hash").toString().toStdString();


            if(passhash == uhash)
            {
                user.id = query.value("id").toInt();
                user.username = query.value("username").toString().toStdString();
                user.password_hash = query.value("password_hash").toString().toStdString();

                return user;
            }
            else
            {
                //uncorrect password
                qDebug() << "Uncorrect password. Try again. Error: " << query.lastError();
                User up;
                up.id = -1;
                return up;
            }
        }

    qDebug() << "Unknown user";
    User up;
    up.id = -2;
    return up;
}


vector<Per> SqliteStorage::getAllDinoPer(int dino_id)
{
    vector<Per> pers;

    QSqlQuery query;
    query.prepare("SELECT * FROM links WHERE dino_id = :dino_id");
    query.bindValue(":dino_id", dino_id);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while(query.next())
    {
        int pid = query.value("per_id").toInt();

        Per p = this->getPerById(pid).value();
        pers.push_back(p);
    }

    return pers;
}


vector<Per> SqliteStorage::getAllDinoPerPage(int dino_id, int page)
{
    int offset = 6 * (page - 1);

    vector<Per> pers;

    QSqlQuery query;
    query.prepare("SELECT * FROM links WHERE dino_id = :dino_id LIMIT 6 OFFSET :offset");
    query.bindValue(":dino_id", dino_id);
    query.bindValue(":offset", offset);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while(query.next())
    {
        int pid = query.value("per_id").toInt();

        Per p = this->getPerById(pid).value();
        pers.push_back(p);
    }

    return pers;
}







vector<Per> SqliteStorage::getAllDinoPerSearch(int dino_id, QString & search)
{
    vector<Per> pers;

    QSqlQuery query;
    query.prepare("SELECT * FROM links WHERE dino_id = :dino_id");
    query.bindValue(":dino_id", dino_id);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    vector<int> ids;

    while(query.next())
    {
        int pid = query.value("per_id").toInt();
        ids.push_back(pid);
    }

    QString s = "%" + search + "%";

    query.clear();

    for(int num : ids)
    {
        query.prepare("SELECT * FROM periods WHERE (id = :id) AND (name || time LIKE :search )");
        query.bindValue(":id", num);
        query.bindValue(":search", s);
        if (!query.exec())
        {
            qDebug() << query.lastError().text();

            abort();
        }
        while (query.next())
        {
            int pid = query.value("per_id").toInt();

            Per p = this->getPerById(pid).value();
            pers.push_back(p);
        }
    }

    return pers;
}













vector<Per> SqliteStorage::getAllNotDinoPer(int dino_id)
{
    vector<Per> pers;

    QSqlQuery query;
    query.prepare("SELECT * FROM links WHERE dino_id = :dino_id");
    query.bindValue(":dino_id", dino_id);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while(query.next())
    {
        int pid = query.value("per_id").toInt();

        Per p = this->getPerById(pid).value();
        pers.push_back(p);
    }

    return pers;
}

vector<Dino> SqliteStorage::getFreeDinos()
{
    vector<Dino> dinos;

    QSqlQuery query;
    query.prepare("SELECT * FROM dinos WHERE id < :dino_id");
    query.bindValue(":dino_id", 1);
    if (!query.exec())
    {
        qDebug() << query.lastError().text();

        abort();
    }

    while (query.next())
    {
       Dino d = getDinoFromQuery(query);
       dinos.push_back(d);
    }
    return dinos;
}


bool SqliteStorage::insertDinoPer(int dino_id, int per_id)
{

    QSqlQuery query;
    query.prepare("INSERT INTO links (dino_id, per_id) VALUES (:dino_id, :per_id)");

    query.bindValue(":dino_id", dino_id);
    query.bindValue(":per_id", per_id);

    if (!query.exec())
    {
        qDebug() << "addlink error" ;
        abort();
        return false;
    }
    return true;
}


bool SqliteStorage::removeDinoPer(int dino_id, int per_id)
{
    QSqlQuery query3;

    query3.prepare("DELETE FROM links WHERE dino_id = :dino_id AND per_id = :per_id");
    query3.bindValue(":dino_id", dino_id);
    query3.bindValue(":per_id",  per_id);


    if (!query3.exec())
    {
        qDebug() << "addtoLinks error:" << query3.lastError();
        return false;
    }
    return true;

}





int SqliteStorage::insertNewUser(const QString & name, const QString & pass, QByteArray & pfp)
{
    QSqlQuery query;

    query.prepare("INSERT INTO users (username, password_hash, pfp) VALUES (:username, :password_hash, :pfp)");

    query.bindValue(":username", name);
    query.bindValue(":password_hash" ,  pass);
    query.bindValue(":pfp" , pfp);


    if (!query.exec())
    {
        qDebug() << "error inserting user";
        abort();
        return -1;
    }

    QVariant var = query.lastInsertId();
    int id =  var.toInt();
    return id;
}


User SqliteStorage::getUserById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec())
    {
        qDebug() << "Unknown error: ";
        abort();
    }

    User u;

    if(query.next())
    {
        u.username = query.value("username").toString().toStdString();
        u.password_hash = query.value("password_hash").toString().toStdString();
        QByteArray pfp = query.value("pfp").toByteArray();
        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData(pfp);

        u.pfp = outPixmap;
    }
    return u;
}

bool SqliteStorage::updatePfp(int id, QByteArray & pic)
{

    QSqlQuery query;

    query.prepare("UPDATE users SET pfp = :pfp WHERE id = :id");
    query.bindValue( ":pfp", pic);
    query.bindValue( ":id", id);

    if( !query.exec() )
    {
        qDebug() << "Error inserting image into table:\n" << query.lastError();
        abort();
        return false;
    }
    return true;
}

int SqliteStorage::namechange(QString & newname, QString & passhash, int uid)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", uid);

    if(!query.exec())
    {
        return -1;
    }

    if(query.next())
    {
        QString uhash = query.value("password_hash").toString();

        if(passhash != uhash)
        {
            return -2;
        }
        else if(passhash == uhash)
        {

            query.prepare("UPDATE users SET username = :username WHERE id = :id");
            query.bindValue(":id", uid);
            query.bindValue(":username", newname);

            if(!query.exec())
            {
                return -3;
            }
        }
    }
    return 0;
}


int SqliteStorage::passchange(QString & npasshash, QString & opasshash, int uid)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", uid);

    if(!query.exec())
    {
        return -1;
    }

    if(query.next())
    {
        QString uhash = query.value("password_hash").toString();

        if(opasshash != uhash)
        {
            return -2;
        }
        else if(opasshash == uhash)
        {
            query.prepare("UPDATE users SET password_hash = :nphash WHERE id = :id");
            query.bindValue(":id", uid);
            query.bindValue(":nphash", npasshash);

            if(!query.exec())
            {
                return -3;
            }
        }
    }

    return 0;

}

