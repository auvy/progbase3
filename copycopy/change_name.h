#ifndef CHANGE_NAME_H
#define CHANGE_NAME_H

#include <QDialog>
#include "storage.h"

#include <QDebug>
#include <QMessageBox>
#include "sqlite_storage.h"
#include <QSqlQuery>
#include <QtSql>
#include <QSqlDatabase>

#include "passhash.h"
namespace Ui {
class change_name;
}

class change_name : public QDialog
{
    Q_OBJECT

public:
    explicit change_name(QWidget *parent = 0, Storage * storage = NULL, int id = 0);
    ~change_name();

private slots:
    void on_confirm_clicked();

    void on_cancel_clicked();

private:
    Ui::change_name *ui;

    Storage * storage_; // <-- STORAGE

    int uid_;
};

#endif // CHANGE_NAME_H
