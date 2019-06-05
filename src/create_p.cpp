#include "create_p.h"
#include "ui_create_p.h"

create_p::create_p(QWidget *parent, int uid, Storage * storage) :
    QDialog(parent),
    ui(new Ui::create_p)
{
    ui->setupUi(this);
    uid_ = uid;
    storage_ = storage;
    pid_ = 0;
}

create_p::~create_p()
{
    delete ui;
}

int create_p::pid()
{
    return pid_;
}

void create_p::on_buttonBox_2_accepted()
{
    if(ui->name->text().isEmpty() || ui->time->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }
    Per p;
    p.name = ui->name->text().toStdString();
    p.time = ui->time->value();

    p.id = this->storage_->insertPer(p);

    pid_ = p.id;

    this->accept();
}

void create_p::on_buttonBox_2_rejected()
{
    this->reject();
}
