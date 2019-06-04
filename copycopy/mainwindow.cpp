#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dino.h"
#include "period.h"
#include "auth.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pd = 1;
    pp = 1;

    storage_ = NULL;

    search_mode = false;

    connect(ui->actionOption2, &QAction::triggered, this, &MainWindow::onOpen);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::XMLImport);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::XMLExport);
    connect(ui->actionView_Account, &QAction::triggered, this, &MainWindow::viewAccount);
    connect(ui->actionRelog, &QAction::triggered, this, &MainWindow::relog);
    connect(ui->actionCreate_new, &QAction::triggered, this, &MainWindow::registerUserData);

    disableButtons();
}

MainWindow::~MainWindow()
{
    if(storage_ != NULL)
    {
        delete this->storage_;
    }
    delete ui;
}


void MainWindow::onOpen()
{
    QString file_path = QFileDialog::getExistingDirectory(
                this,              // parent
                "Dialog Caption",  // caption
                "",                // directory to start with
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);  // file name filter

    if(!file_path.isEmpty())
    {
        this->loadfrom(file_path);

        logNotEmpty();
    }
}

void MainWindow::registerUserData()
{
    createacc * cac = new createacc(this, storage_);
    cac->exec();

    disableButtons();

    uid = cac->getUID();

    cleantext();

    ui->listWidget->clear();
    ui->listWidget2->clear();


    if(uid > 0)
    {
        ui->add->setEnabled(true);
        ui->edit->setEnabled(false);
        ui->remove->setEnabled(false);
        ui->edit2->setEnabled(false);
        ui->add2->setEnabled(false);
        ui->remove2->setEnabled(false);
        ui->actionView_Account->setEnabled(true);
        ui->actionImport->setEnabled(true);
        ui->actionExport->setEnabled(true);
        ui->searchd->setEnabled(true);
        ui->xsearchd->setEnabled(true);
        ui->left->setEnabled(true);
        ui->right->setEnabled(true);
        ui->left_2->setEnabled(true);
        ui->right_2->setEnabled(true);
        ui->refresh->setEnabled(true);
        this->fillWListDino(uid);

    }

    ui->actionCreate_new->setEnabled(true);
    ui->actionRelog->setEnabled(true);

    ui->pagend->setText(QString::number(pd));
    ui->pagenp->setText(QString::number(pp));

}

void MainWindow::loadfrom(QString & path)
{
    std::string filenamestd;
    filenamestd = path.toUtf8().constData();

    SqliteStorage * sql_storage = new SqliteStorage(filenamestd);
\
//    delete this->storage_;

    storage_ = sql_storage;

    if(this->storage_->open() == false)
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Cannot open file!!!",
                    QMessageBox::Ok);
        return;
    }
}

void MainWindow::disableButtons()
{
    ui->edit->setEnabled(false);
    ui->remove->setEnabled(false);
    ui->edit2->setEnabled(false);
    ui->add2->setEnabled(false);
    ui->remove2->setEnabled(false);
    ui->add->setEnabled(false);
    ui->actionView_Account->setEnabled(false);
    ui->actionImport->setEnabled(false);
    ui->actionExport->setEnabled(false);
    ui->actionCreate_new->setEnabled(false);
    ui->actionRelog->setEnabled(false);
    ui->searchd->setEnabled(false);
    ui->xsearchd->setEnabled(false);
    ui->left->setEnabled(false);
    ui->right->setEnabled(false);
    ui->refresh->setEnabled(false);
    ui->left_2->setEnabled(false);
    ui->right_2->setEnabled(false);
}


void MainWindow::logNotEmpty()
{
    auth * au = new auth(this, storage_);
    au->exec();

    disableButtons();

    uid = au->getUID();

    ui->listWidget->clear();
    ui->listWidget2->clear();


    if(uid > 0)
    {
        ui->add->setEnabled(true);
        ui->edit->setEnabled(false);
        ui->remove->setEnabled(false);
        ui->edit2->setEnabled(false);
        ui->add2->setEnabled(false);
        ui->remove2->setEnabled(false);
        ui->actionView_Account->setEnabled(true);
        ui->actionImport->setEnabled(true);
        ui->actionExport->setEnabled(true);
        ui->searchd->setEnabled(true);
        ui->xsearchd->setEnabled(true);
        ui->left->setEnabled(true);
        ui->right->setEnabled(true);
        ui->left_2->setEnabled(true);
        ui->right_2->setEnabled(true);
        ui->refresh->setEnabled(true);
        this->fillWListDino(uid);

    }

    ui->actionCreate_new->setEnabled(true);
    ui->actionRelog->setEnabled(true);

    ui->pagend->setText(QString::number(pd));
    ui->pagenp->setText(QString::number(pp));

}






void MainWindow::viewAccount()
{
    usermenu * u = new usermenu(this, uid, storage_);
    u->exec();
    return;
}

void MainWindow::relog()
{
    logNotEmpty();
}




QDomElement dinoToDomElmw(QDomDocument & doc, Dino & dino)
{
    QDomElement dino_el = doc.createElement("dino");

    dino_el.setAttribute("id", dino.id);
    dino_el.setAttribute("name", dino.name.c_str());
//    dino_el.setAttribute("period", dino.per.c_str());
    dino_el.setAttribute("family", dino.fam.c_str());
    dino_el.setAttribute("discovery", dino.disc);
    dino_el.setAttribute("mass", dino.mass);

    return dino_el;
}

bool tofilemw(QDomDocument & doc, string & filename)
{
    QString xml_text = doc.toString(4);

    QString s_filename = QString::fromStdString(filename);
    QFile file(s_filename);
    if(!file.open(QFile::WriteOnly))
    {
        qDebug() << "Couldn't open file to write : " << s_filename;
        return false;
    }
    QTextStream ts(&file);
    ts << xml_text;
    file.close();

    return true;
}

void MainWindow::XMLImport()
{


        QString file_path = QFileDialog::getOpenFileName(this,
                tr("Open XML File"), "",
                tr("XML (*.xml)"));

        string filepath = file_path.toUtf8().constData();

        if(!file_path.isEmpty())
        {
            this->XMLloadfromstr(filepath);
        }

        ui->listWidget->clear();

        this->fillWListDino(uid);

        ui->listWidget2->clear();
}


void MainWindow::XMLExport()
{
    QString file_path = QFileDialog::getSaveFileName(
                this,              // parent
                "Dialog Caption",  // caption
                "",                // directory to start with
                "",
                nullptr,
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);  // file name filter

    vector<Dino> dinos = this->storage_->getAllDinos();

    QDomDocument doc;
    QDomElement root = doc.createElement("dinos");

    for(Dino & dino : dinos)
    {
        QDomElement dino_el =  dinoToDomElmw(doc, dino);
        root.appendChild(dino_el);
    }

    doc.appendChild(root);
    string filename = file_path.toUtf8().constData();
    tofilemw(doc, filename);

    return;
}

bool errorcheckmw(QString & text, QDomDocument & doc)
{
    QString errorMessage;
    int errorLine;
    int errorCol;
    bool is_parsed = doc.setContent(text, &errorMessage, &errorLine, &errorCol);
    if(!is_parsed)
    {
        qDebug() << "Error parsing xml: " << errorMessage;
        qDebug() << "In line:  " << errorLine;
        qDebug() << "In colu:  " << errorCol;
        return false;
    }
    return true;
}

Dino domElementToDinomw(QDomElement & element)
{
    Dino d;
//    d.id = element.attributeNode("id").value().toInt();
    d.name = element.attributeNode("name").value().toStdString();
//    d.per = element.attributeNode("period").value().toStdString();
    d.fam = element.attributeNode("family").value().toStdString();
    d.disc = element.attributeNode("discovery").value().toInt();
    d.mass = element.attributeNode("mass").value().toFloat();
    d.user_id = 0;
    return d;
}




bool MainWindow::XMLloadfromstr(string filename)
{
    vector<Dino> dinos;

    QString s_filename = QString::fromStdString(filename);
    QFile s_file(s_filename);
    bool is_opened = s_file.open(QFile::ReadOnly);
    if (!is_opened)
    {
       qDebug() << "file wasnt found";
       return false;
    }

    QTextStream ts(&s_file);
    QString text = ts.readAll();
    QDomDocument doc;
    if(!errorcheckmw(text, doc))
    {
        return false;
    }

    QDomElement root = doc.documentElement();
    for(int i = 0; i < root.childNodes().size(); i++)
    {
        QDomNode node = root.childNodes().at(i);
        if(node.isElement())
        {
            QDomElement element = node.toElement();
            Dino dino = domElementToDinomw(element);
            dinos.push_back(dino);
        }
    }

    s_file.close();

    for(Dino & dino : dinos)
    {
        Dino dvno = dino;
        dvno.user_id = uid;


        if(this->storage_->insertDino(dvno) == 0)
        {
            qDebug() << "error inserting";
        }

    }


    return true;
}


void MainWindow::fillWListDino(int uid)
{
    QVector<Dino> dinos = QVector<Dino>::fromStdVector(storage_->getAllUserDinoPage(uid, pd));

    QVariant var;

    for(Dino & dino : dinos)
    {
        string stext = dino.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(dino);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(new_item);
    }
}


void MainWindow::fillWListDinoSearch(int uid)
{
    QVector<Dino> dinos = QVector<Dino>::fromStdVector(storage_->getAllUserDinoPageSearch(uid, pd, search_));

    QVariant var;

    for(Dino & dino : dinos)
    {
        string stext = dino.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(dino);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(new_item);
    }
}


void MainWindow::fillWListPer(int did)
{
    QVector<Per> pers =  QVector<Per>::fromStdVector(storage_->getAllDinoPerPage(did, pp));

    QVariant var;
    for(Per & per : pers)
    {
        string stext = per.name;
        QString text = QString::fromStdString(stext);
        QListWidgetItem * new_item = new QListWidgetItem(text);
        var = QVariant::fromValue(per);
        new_item->setData(Qt::UserRole, var);
        ui->listWidget2->addItem(new_item);
    }
}



bool MainWindow::fileWrite(QString &path, QString &data)
{
    QFile file(path);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(
                    this,
                    "WARNING",
                    "Cannot create storage!!!",
                    QMessageBox::Ok);
        return false;
    }

    QTextStream out(&file);
    out << data;
    file.close();
    return true;
}

void MainWindow::on_add_clicked()
{
    add_d window(this);
    if(window.exec())
    {
        QVariant var;
        Dino dino = window.getDino();
        dino.user_id = uid;
        dino.id = this->storage_->insertDino(dino);

        QListWidgetItem * item = new QListWidgetItem;
        var.setValue(dino); 
        const QString name = QString::fromUtf8(dino.name.c_str());
        item->setText(name);
        item->setData(Qt::UserRole, var);
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_edit_clicked()
{
    QListWidgetItem * item = ui->listWidget->currentItem();

    if(item != NULL)
    {
        Dino dino;
        QVariant var;


        dino = item->data(Qt::UserRole).value<Dino>();

        edit_d window(dino, this, storage_);

        if(window.exec())
        {
            ui->listWidget2->clear();
            this->fillWListPer(dino.id);
        }

    }

//    this->storage_->close();
}

void MainWindow::on_remove_clicked()
{
    QListWidgetItem * item = ui->listWidget->currentItem();

    if(item != NULL)
    {
        QMessageBox::StandardButton remove;
           remove = QMessageBox::question(
               this,
               "Remove",
               "Are you sure?",
               QMessageBox::Yes|QMessageBox::No);

        if (remove == QMessageBox::Yes)
        {
               Dino dino;

               dino = item->data(Qt::UserRole).value<Dino>();

               this->storage_->removeDino(dino.id);

               delete ui->listWidget->takeItem(ui->listWidget->row(item));
        }
    }


}

void MainWindow::on_add2_clicked()
{
    QListWidgetItem * qdino = ui->listWidget->currentItem();
    Dino d = qdino->data(Qt::UserRole).value<Dino>();
    int id = d.id;
    create_p window(this, id, storage_);
    if(window.exec())
    {
        int pid = window.pid();

        if(pid != 0)
        {
            this->storage_->insertDinoPer(id, pid);
        }

        ui->listWidget2->clear();
        this->fillWListPer(id);
    }
}

void MainWindow::on_edit2_clicked()
{
    QListWidgetItem * item = ui->listWidget2->currentItem();

    if(item != NULL)
    {
        Per per = item->data(Qt::UserRole).value<Per>();
        QVariant variant;

        edit_p window(per, this);

        if(window.exec())
        {
            per = window.getPer();
            this->storage_->updatePer(per);

            variant.setValue(per);
            const QString name = QString::fromUtf8(per.name.c_str());
            item->setText(name);
            item->setData(Qt::UserRole, variant);
        }
    }
}

void MainWindow::on_remove2_clicked()
{
    QMessageBox::StandardButton remove;
       remove = QMessageBox::question(
           this,
           "Remove",
           "Are you sure?",
           QMessageBox::Yes|QMessageBox::No);

    if (remove == QMessageBox::Yes)
    {
        QListWidgetItem * qdino = ui->listWidget->currentItem();
        Dino d = qdino->data(Qt::UserRole).value<Dino>();
        int did = d.id;

        QListWidgetItem * iper = ui->listWidget2->currentItem();

        if(iper != NULL)
        {
            Per per = iper->data(Qt::UserRole).value<Per>();
            int pid = per.id;

            if(!this->storage_->removeDinoPer(did, pid))
            {
                qDebug() << "Something went wrong";
            }

            delete ui->listWidget2->takeItem(ui->listWidget2->row(iper));
        }
    }

//    this->storage_->close();
}

void MainWindow::on_listWidget2_itemSelectionChanged()
{
    ui->edit2->setEnabled(false);
    ui->remove2->setEnabled(false);

    if(ui->listWidget2->count() >= 1)
    {
        QListWidgetItem * item = ui->listWidget2->currentItem();

        ui->edit2->setEnabled(true);
        ui->remove2->setEnabled(true);

        Per per = item->data(Qt::UserRole).value<Per>();

        ui->lselected_2->setText("Selected period:");
        ui->lplname->setText("Name:");
        ui->lpltime->setText("Length:");

        ui->lpname->setText(QString::fromUtf8(per.name.c_str()));
        ui->lptime->setText(QString::number(per.time));
    }


}

void MainWindow::on_listWidget_itemSelectionChanged()
{

    ui->edit->setEnabled(false);
    ui->remove->setEnabled(false);
    ui->add2->setEnabled(false);
    ui->edit2->setEnabled(false);
    ui->remove2->setEnabled(false);

    if(ui->listWidget->count() >= 1)
    {
        QListWidgetItem * item = ui->listWidget->currentItem();

        Dino dino = item->data(Qt::UserRole).value<Dino>();

        ui->lselected->setText("Selected dino:");
        ui->ldlname->setText("Name:");
        ui->ldlfam->setText("Family:");
        ui->ldldisc->setText("Discovered:");
        ui->ldlmass->setText("Mass");

        ui->ldname->setText(QString::fromUtf8(dino.name.c_str()));
        ui->ldfam-> setText(QString::fromUtf8(dino.fam.c_str()));
        ui->lddisc->setText(QString::number(dino.disc));
        ui->ldmass->setText(QString::number(dino.mass));
        ui->listWidget2->clear();

        this->fillWListPer(dino.id);


        ui->edit->setEnabled(true);
        ui->remove->setEnabled(true);

        ui->add2->setEnabled(true);
    }


//  }
    //now this to listselect1

}


void MainWindow::cleantext()
{
    ui->lselected->setText("");
    ui->ldlname->setText("");
    ui->ldlfam->setText("");
    ui->ldldisc->setText("");
    ui->ldlmass->setText("");

    ui->ldname->setText("");
    ui->ldfam-> setText("");
    ui->lddisc->setText("");
    ui->ldmass->setText("");

    ui->lselected_2->setText("");
    ui->lplname->setText("");
    ui->lpltime->setText("");

    ui->lpname->setText("");
    ui->lptime->setText("");
}

void MainWindow::refresh()
{
    cleantext();

    ui->listWidget->clear();

    this->fillWListDino(uid);

    ui->listWidget2->clear();
}

void MainWindow::on_refresh_clicked()
{
    refresh();
}

void MainWindow::on_left_clicked()
{
    ui->edit->setEnabled(false);
    ui->remove->setEnabled(false);

    if(pd > 1)
    {


        ui->listWidget->clear();
        ui->listWidget2->clear();

        if(search_mode == false)
        {
            pd--;

            cleantext();

            this->fillWListDino(uid);

            ui->pagend->setText(QString::number(pd));
        }
        else
        {
            pd--;

            cleantext();

            this->fillWListDinoSearch(uid);

            ui->pagend->setText(QString::number(pd));
        }
    }
}


void MainWindow::on_right_clicked()
{
    ui->edit->setEnabled(false);
    ui->remove->setEnabled(false);

    int size = ceil((double)(storage_->getAllUserDino(uid).size())/6);
    int size2 = ceil((double)(storage_->getAllUserDinoSearch(uid, search_).size())/6);

    int check = 1;

    if(search_mode == false)
    {
        check = size;
    }
    else check = size2;

    if(pd < check)
    {

        ui->listWidget->clear();
        ui->listWidget2->clear();

        if(search_mode == false)
        {
            pd++;

            cleantext();

            this->fillWListDino(uid);

            ui->pagend->setText(QString::number(pd));
        }
        else
        {
            pd++;

            cleantext();

            this->fillWListDinoSearch(uid);

            ui->pagend->setText(QString::number(pd));
        }
    }
}

void MainWindow::on_searchd_clicked()
{
    search_mode = true;
    pd = 1;
    pp = 1;

    search_ = ui->searchdf->text();

    ui->listWidget->clear();
    ui->listWidget2->clear();

    cleantext();

    this->fillWListDinoSearch(uid);

    ui->pagend->setText(QString::number(pd));


}

void MainWindow::on_xsearchd_clicked()
{
    search_mode = false;

    ui->listWidget->clear();
    ui->listWidget2->clear();

    pd = 1;
    pp = 1;

    cleantext();

    this->fillWListDino(uid);

    ui->pagend->setText(QString::number(pd));
}


int MainWindow::idofseldino()
{
    QListWidgetItem * item = ui->listWidget->currentItem();

    Dino dino = item->data(Qt::UserRole).value<Dino>();

    return dino.id;
}

void MainWindow::on_left_2_clicked()
{
    ui->edit2->setEnabled(false);
    ui->remove2->setEnabled(false);

    int did = idofseldino();

    if(pp > 1)
    {


        ui->listWidget2->clear();

           pp--;

            cleantext();

            this->fillWListPer(did);

            ui->pagenp->setText(QString::number(pp));

    }
}


void MainWindow::on_right_2_clicked()
{
    ui->edit2->setEnabled(false);
    ui->remove2->setEnabled(false);

    int did = idofseldino();

    int size = ceil((double)(storage_->getAllDinoPer(did).size())/6);
//    int size2 = ceil((double)(storage_->getAllUserDinoSearch(uid, search_).size())/6);


    if(pp < size)
    {
        ui->listWidget2->clear();

            pp++;

            cleantext();

            this->fillWListPer(did);

            ui->pagenp->setText(QString::number(pp));
    }
}
