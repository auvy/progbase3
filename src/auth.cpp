#include "auth.h"
#include "ui_auth.h"

#include <QDebug>
#include <QMessageBox>
#include "sqlite_storage.h"
#include <QtSql>
#include <QSqlDatabase>

#include <QCryptographicHash>

auth::auth(QWidget *parent, Storage * stor) :
    QDialog(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);
    astorage_ = stor;
}

auth::~auth()
{
    delete ui;
}

int auth::getUID()
{
    int a = uid;
    return a;
}


void auth::on_loginb_clicked()
{
    if(ui->password->text().isEmpty() || ui->login->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }

    string username = ui->login->text().toStdString().c_str();
    string password = ui->password->text().toStdString().c_str();

    if(astorage_->getUserAuth(username, password) != nullopt)
    {
        if(astorage_->getUserAuth(username, password).value().id == -1)
        {
            QMessageBox::warning(
                        this,
                        "WARNING",
                        "Uncorrect password. Try again",
                        QMessageBox::Ok);
            return;
        }
        else if(astorage_->getUserAuth(username, password).value().id == -2)
        {
            QMessageBox::warning(
                        this,
                        "WARNING",
                        "Unknown user. Try again",
                        QMessageBox::Ok);
            return;
        }
        else
        {
            uid = astorage_->getUserAuth(username, password).value().id;

            this->accept();
        }
    }
    else if(astorage_->getUserAuth(username, password) == nullopt)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Something went terribly wrong",
                    QMessageBox::Ok);
        return;
    }

}


void auth::on_back_clicked()
{
    this->reject();
}



void auth::on_create_clicked()
{
    if(ui->password->text().isEmpty() || ui->login->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }

    string username = ui->login->text().toStdString().c_str();
    string password = ui->password->text().toStdString().c_str();



    QString fhash = hashPassword(QString::fromUtf8(password.c_str()));
    string passhash = fhash.toUtf8().constData();

    QString phash = hashPassword(ui->password->text());

    if(astorage_->getUserAuth(username, password).value().id == -1)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "This login is taken",
                    QMessageBox::Ok);
        return;
    }

    QByteArray empty;

    int usid = this->astorage_->insertNewUser(ui->login->text(), phash, empty);

    if(usid == -1)
    {
            QMessageBox::warning(
                        this,
                        "WARNING",
                        "Unknown error",
                        QMessageBox::Ok);
            return;
    }

    uid = usid;

    this->accept();
}
