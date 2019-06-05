#ifndef CREATE_P_H
#define CREATE_P_H

#include <QDialog>

#include <QDebug>
#include <QMessageBox>
#include "period.h"
#include "storage.h"

namespace Ui {
class create_p;
}

class create_p : public QDialog
{
    Q_OBJECT

public:
    explicit create_p(QWidget *parent = 0, int uid = 0, Storage * storage = NULL);
    int pid();

    ~create_p();

private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

private:
    Ui::create_p *ui;
    Storage * storage_;
    int uid_;
    int pid_;
};

#endif // CREATE_P_H
