#ifndef CREATEACC_H
#define CREATEACC_H

#include <QDialog>
#include "storage.h"
#include <QtCore>
#include <QSqlDatabase>
#include <QtSql>
#include <QtWidgets>

#include "change_pass.h"
#include "change_name.h"

namespace Ui {
class createacc;
}

class createacc : public QDialog
{
    Q_OBJECT

public:
    explicit createacc(QWidget *parent = 0, Storage * storage = NULL);
    int getUID();

    ~createacc();

private slots:
    void on_create_clicked();

    void on_back_clicked();

    void on_pushButton_clicked();

private:
    Ui::createacc *ui;
    int uid_;
    Storage * storage_;
    QByteArray pfp_;

};

#endif // CREATEACC_H
