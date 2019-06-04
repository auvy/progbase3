#include "usermenu.h"
#include "ui_usermenu.h"

usermenu::usermenu(QWidget *parent, int uid, Storage * storage) :
    QDialog(parent),
    ui(new Ui::usermenu)
{
    ui->setupUi(this);
    imageBuffer = nullptr;
    storage_ = storage;
    uid_ = uid;

    this->refresh();

}



void usermenu::refresh()
{
    User u = this->storage_->getUserById(uid_);

    ui->name->setText(QString::fromStdString((u.username.c_str())));
    ui->pfp->setPixmap(u.pfp);
}

usermenu::~usermenu()
{
    delete ui;
}

void usermenu::on_pushButton_clicked()
{

    QString file_path = QFileDialog::getOpenFileName(
                this,              // parent
                "Dialog Caption",  // caption
                "",                // directory to start with
                "",
                nullptr,
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);  // file name filter

    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray inByteArray = file.readAll();

    if(!this->storage_->updatePfp(uid_, inByteArray))
    {
        qDebug() << "failed to update";
        return;
    }

    this->refresh();
}









void usermenu::on_chname_clicked()
{
    change_name * chn = new change_name(this, storage_, uid_);
    chn->exec();
    this->refresh();
}

void usermenu::on_chpass_clicked()
{
    change_pass * chp = new change_pass(this, storage_, uid_);
    chp->exec();
    this->refresh();
}

void usermenu::on_buttonBox_accepted()
{
    this->accept();
}

void usermenu::on_buttonBox_rejected()
{
    this->reject();
}
