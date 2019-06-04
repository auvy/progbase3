#include "change_name.h"
#include "ui_change_name.h"

change_name::change_name(QWidget *parent, Storage * storage, int uid) :
    QDialog(parent),
    ui(new Ui::change_name)
{
    ui->setupUi(this);
    storage_ = storage;
    uid_ = uid;

}

change_name::~change_name()
{
    delete ui;
}

void change_name::on_confirm_clicked()
{
    if(ui->pass->text().isEmpty() || ui->newname->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }

    QString oldpass = ui->pass->text();

    QString opasshash = hashPassword(oldpass);
    QString newname = ui->newname->text();

    int result = this->storage_->namechange(newname, opasshash, uid_);

    if(result == -1)
    {
        QMessageBox::warning(
                    this,
                    "ERROR",
                    "Failed to find the user",
                    QMessageBox::Ok);
        return;
    }
    else if(result == -2)
    {
        QMessageBox::warning(
                    this,
                    "ERROR",
                    "Incorrect password",
                    QMessageBox::Ok);
        return;
    }
    else if(result == -3)
    {
        QMessageBox::warning(
                    this,
                    "ERROR",
                    "Failed to update name",
                    QMessageBox::Ok);
        return;
    }
    else
    {
        QMessageBox::information(
                    this,
                    "SUCCESS",
                    "Name changed successfully",
                    QMessageBox::Ok);
    }

    this->accept();
}



void change_name::on_cancel_clicked()
{
    this->reject();
}
