#include "change_pass.h"
#include "ui_change_pass.h"

change_pass::change_pass(QWidget *parent, Storage * storage, int uid) :
    QDialog(parent),
    ui(new Ui::change_pass)
{
    ui->setupUi(this);
    storage_ = storage;
    uid_ = uid;

}

change_pass::~change_pass()
{
    delete ui;
}

void change_pass::on_confirm_clicked()
{
    if(ui->oldpass->text().isEmpty() || ui->newpass->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }

    QString opasshash = hashPassword(ui->oldpass->text());
    QString npasshash = hashPassword(ui->newpass->text());

    int result = this->storage_->passchange(npasshash, opasshash, uid_);

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
                    "WRONG password",
                    QMessageBox::Ok);
        return;
    }
    else if(result == -3)
    {
        QMessageBox::warning(
                    this,
                    "ERROR",
                    "Failed to update password",
                    QMessageBox::Ok);
        return;
    }
    else
    {
        QMessageBox::information(
                    this,
                    "SUCCESS",
                    "Password changed successfully",
                    QMessageBox::Ok);
    }

    this->accept();


}

void change_pass::on_cancel_clicked()
{
    this->reject();
}
