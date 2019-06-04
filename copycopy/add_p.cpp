#include "add_p.h"
#include "ui_add_p.h"
#include "dino.h"
#include "mainwindow.h"

#include <QDebug>
#include <QMessageBox>

#include <QFileDialog>
#include <QMessageBox>

#include <QSqlDatabase>


add_p::add_p(QWidget *parent, int did, Storage * storage) :
    QDialog(parent),
    ui(new Ui::add_p)
{
    ui->setupUi(this);
    did_ = did;
    storage_ = storage;

    this->fillWListPer();
}

add_p::~add_p()
{
    delete ui;
}

Per add_p::getPer()
{
    return this->per;
}


void add_p::on_cancel_clicked()
{
    this->reject();
}


void add_p::fillWListPer()
{
    vector<Per> pers = storage_->getAllPers();
    vector<Per> dpers = storage_->getAllDinoPer(did_);


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
        ui->listWidget2_4->addItem(new_item);
    }
}


void add_p::on_add_clicked()
{
    if(ui->listWidget2_4->count() >= 1)
    {
        QListWidgetItem * item = ui->listWidget2_4->currentItem();

        Per per = item->data(Qt::UserRole).value<Per>();

        int pid = per.id;
        int did = did_;

        if(!this->storage_->insertDinoPer(did, pid))
        {
            qDebug() << "errer";
            return;
        }
    }

    this->accept();
}


void add_p::on_listWidget2_4_itemSelectionChanged()
{
    QListWidgetItem * item = ui->listWidget2_4->currentItem();

    Per per = item->data(Qt::UserRole).value<Per>();

    ui->lselected_5->setText("Selected period:");
    ui->lplname_4->setText("Name:");
    ui->lpltime_4->setText("Length:");

    ui->lpname_4->setText(QString::fromUtf8(per.name.c_str()));
    ui->lptime_4->setText(QString::number(per.time));
}
