#ifndef USERMENU_H
#define USERMENU_H

#include <QDialog>
#include "storage.h"
#include <QtCore>
#include <QSqlDatabase>
#include <QtSql>
#include <QtWidgets>

#include "change_pass.h"
#include "change_name.h"


namespace Ui {
class usermenu;
}

class usermenu : public QDialog
{
    Q_OBJECT

public:
    explicit usermenu(QWidget *parent = 0, int uid = 0, Storage * storage = NULL);
    ~usermenu();

private slots:


    void on_pushButton_clicked();

    void refresh();


    void on_chname_clicked();

    void on_chpass_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::usermenu *ui;
    QPixmap * imageBuffer;
    int uid_;
    Storage * storage_;

};

#endif // USERMENU_H
