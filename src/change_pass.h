#ifndef CHANGE_PASS_H
#define CHANGE_PASS_H

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
class change_pass;
}

class change_pass : public QDialog
{
    Q_OBJECT

public:
    explicit change_pass(QWidget *parent = 0, Storage * storage = NULL, int id = 0);
    ~change_pass();

private slots:

    void on_confirm_clicked();

    void on_cancel_clicked();

private:
    Ui::change_pass *ui;

    Storage * storage_; // <-- STORAGE

    int uid_;
};

#endif // CHANGE_PASS_H
