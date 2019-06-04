#ifndef EDIT_D_H
#define EDIT_D_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>

#include "period.h"
#include "dino.h"
#include "storage.h"
#include "period.h"

namespace Ui {
class edit_d;
}

class edit_d : public QDialog
{
    Q_OBJECT

public:
    explicit edit_d(Dino & dino, QWidget *parent = 0, Storage * storage = NULL);
    ~edit_d();
    Dino getDino();

private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();
    
    void on_listWidget2_4_itemSelectionChanged();

    void on_listWidget2_5_itemSelectionChanged();

private:
    Ui::edit_d *ui;
    QIntValidator int_val;
    QDoubleValidator double_val;
    QRegExpValidator regx_val;
    Dino dino;
    Storage * storage_;

    void fillWListPer();
    void fillWListPer(int did);
};

#endif // EDIT_D_H
