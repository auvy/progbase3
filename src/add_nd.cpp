#include "add_nd.h"
#include "ui_add_nd.h"

add_nd::add_nd(QWidget *parent, int uid, Storage * storage) :
    QDialog(parent),
    ui(new Ui::add_nd)
{
    ui->setupUi(this);
    uid_ = uid;
    storage_ = storage;

    this->fillWListDino();


}

add_nd::~add_nd()
{
    delete ui;
}

void add_nd::on_add_clicked()
{
    QListWidgetItem * item = ui->listWidget_2->currentItem();


    Dino d = item->data(Qt::UserRole).value<Dino>();

    int did = d.id;


    QSqlQuery query;
    query.prepare("UPDATE dinosaurs SET user_id = :uid WHERE id = :id");
    query.bindValue(":uid", uid_);
    query.bindValue(":id", did);

    if (!query.exec())
    {
        qDebug() << "adddino error" ;
        abort();
    }
    this->accept();
}

void add_nd::on_cancel_clicked()
{
    this->reject();
}

void add_nd::on_listWidget_2_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget_2->currentItem();

    Dino dino = item->data(Qt::UserRole).value<Dino>();

    ui->lselected_2->setText("Selected dino:");
    ui->ldlname_2->setText("Name:");
    ui->ldlfam_2->setText("Family:");
    ui->ldldisc_2->setText("Discovered:");
    ui->ldlmass_2->setText("Mass");

    ui->ldname_2->setText(QString::fromUtf8(dino.name.c_str()));
    ui->ldfam_2-> setText(QString::fromUtf8(dino.fam.c_str()));
    ui->lddisc_2->setText(QString::number(dino.disc));
    ui->ldmass_2->setText(QString::number(dino.mass));
}


void add_nd::fillWListDino()
{
    vector<Dino> dinos = storage_->getFreeDinos();

    QVariant var;
    for(Dino & dino : dinos)
    {
        string stext = dino.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(dino);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget_2->addItem(new_item);
    }

}


