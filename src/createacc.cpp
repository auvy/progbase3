#include "createacc.h"
#include "ui_createacc.h"

createacc::createacc(QWidget *parent, Storage * storage) :
    QDialog(parent),
    ui(new Ui::createacc)
{
    ui->setupUi(this);
    uid_ = 0;
    storage_ = storage;

}

createacc::~createacc()
{
    delete ui;
}

int createacc::getUID()
{
    int a = uid_;
    return a;
}

void createacc::on_create_clicked()
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

    if(storage_->getUserAuth(username, password).value().id != -2)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "This login is taken",
                    QMessageBox::Ok);
        return;
    }

    uid_ = this->storage_->insertNewUser(ui->login->text(), fhash, pfp_);

    if(uid_ < 1)
    {
        qDebug() << "failed to insert";
        abort();
    }

    this->accept();
}

void createacc::on_back_clicked()
{
    this->reject();
}

void createacc::on_pushButton_clicked()
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
    QByteArray pfp = file.readAll();

    pfp_ = pfp;

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(pfp_);
    ui->pfp->setPixmap(outPixmap);

}
