#include "edit_d.h"
#include "ui_edit_d.h"

#include <QDebug>
#include <QMessageBox>

edit_d::edit_d(Dino & dino, QWidget *parent, Storage * storage) :
    QDialog(parent),
    ui(new Ui::edit_d)
{
    storage_ = storage;


    ui->setupUi(this);

    double_val.setNotation(QDoubleValidator::StandardNotation);

    QLocale locale(QLocale::C);
    double_val.setLocale(locale);


    this->dino.id = dino.id;

    ui->name->setText(QString::fromUtf8(dino.name.c_str()));
    ui->fam->setText(QString::fromUtf8(dino.fam.c_str()));
    ui->disc->setValue(dino.disc);
    ui->mass->setValue(dino.mass);

    ui->name->setValidator(&regx_val);
    ui->fam->setValidator(&regx_val);


    fillWListPer();
    fillWListPer(dino.id);



}

edit_d::~edit_d()
{
    delete ui;
}


Dino edit_d::getDino()
{
    return this->dino;
}

void edit_d::on_buttonBox_2_accepted()
{
    if(ui->name->text().isEmpty()  || ui->fam->text().isEmpty() || ui->disc->text().isEmpty() || ui->mass->text().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Some fields are empty",
                    QMessageBox::Ok);
        return;
    }


    QMessageBox::StandardButton edit = QMessageBox::question(
           this,
           "Edit",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);


    if (edit == QMessageBox::Yes)
    {
        this->dino.name = ui->name->text().toStdString();
        this->dino.fam = ui->fam->text().toStdString();
        this->dino.disc = ui->disc->value();
        this->dino.mass = ui->mass->value();

        if(!this->storage_->updateDino(dino))
        {
            qDebug() << "failed to update";
            return;
        }


        if(ui->listWidget2_4->count() >= 1)
        {
            QListWidgetItem * iper = ui->listWidget2_4->currentItem();

            if(iper != NULL)
            {
                Per per = iper->data(Qt::UserRole).value<Per>();

                int did = dino.id;
                int pid = per.id;

                if(!this->storage_->removeDinoPer(did, pid))
                {
                    qDebug() << "Something went wrong";
                    abort();
                }
            }

        }


        if(ui->listWidget2_5->count() >= 1)
        {
            QListWidgetItem * item = ui->listWidget2_5->currentItem();

            if(item != NULL)
            {
                Per per = item->data(Qt::UserRole).value<Per>();

                int pid = per.id;
                int did = dino.id;


                if(!this->storage_->insertDinoPer(did, pid))
                {
                    qDebug() << "error linking";
                    abort();
                }
            }

        }
    }



    this->accept();
}



void edit_d::on_buttonBox_2_rejected()
{
    this->reject();
}

void edit_d::fillWListPer(int did)
{
    QVector<Per> pers =  QVector<Per>::fromStdVector(storage_->getAllDinoPer(did));

    QVariant var;
    for(Per & per : pers)
    {
        string stext = per.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(per);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget2_4->addItem(new_item);
    }
}


void edit_d::fillWListPer()
{
    vector<Per> pers = storage_->getAllPers();
    vector<Per> dpers = storage_->getAllDinoPer(dino.id);


    vector<int> allpids;

    for(Per & curr : pers)
    {
        int nw = curr.id;
        allpids.push_back(nw);
    }


    vector<int> dinpids;

    for(Per & curr : dpers)
    {
        int nw = curr.id;
        dinpids.push_back(nw);
    }

    vector<int> cross;

            for(int & idd : allpids)
            {
                if(std::find(dinpids.begin(), dinpids.end(), idd) != dinpids.end())
                {
                    /* v contains x */
                }
                else
                {
                    cross.push_back(idd);
                }

            }

    QVector<Per> crossp;


    for(int & ok : cross)
    {
        Per p = storage_->getPerById(ok).value();

        crossp.push_back(p);
    }


    QVariant var;

    for(Per & per : crossp)
    {
        string stext = per.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(per);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget2_5->addItem(new_item);
    }
}


void edit_d::on_listWidget2_4_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget2_4->currentItem();

    if(item != NULL)
    {
        Per per = item->data(Qt::UserRole).value<Per>();

        ui->lplname_4->setText("Name:");
        ui->lpltime_4->setText("Length:");

        ui->lpname_4->setText(QString::fromUtf8(per.name.c_str()));
        ui->lptime_4->setText(QString::number(per.time));

    }


}

void edit_d::on_listWidget2_5_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget2_5->currentItem();

    if(item != NULL)
    {
        Per per = item->data(Qt::UserRole).value<Per>();

        ui->lplname_5->setText("Name:");
        ui->lpltime_5->setText("Length:");

        ui->lpname_5->setText(QString::fromUtf8(per.name.c_str()));
        ui->lptime_5->setText(QString::number(per.time));
    }

}
