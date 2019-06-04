#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "storage.h"
#include "sqlite_storage.h"


#include <QMainWindow>
#include <QtCore>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileInfo>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QTextStream>
#include <string>
#include <vector>
#include <QtXml>
#include <QPixmap>


#include "add_d.h"
#include "add_p.h"
#include "edit_d.h"
#include "edit_p.h"
#include "ui_mainwindow.h"
#include "usermenu.h"
#include "createacc.h"
#include "create_p.h"

namespace Ui {class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void onNew();

    void onOpen();    

    void on_add_clicked();

    void on_edit_clicked();

    void on_remove_clicked();

    void on_add2_clicked();

    void on_edit2_clicked();

    void on_remove2_clicked();

    void on_listWidget2_itemSelectionChanged();

    void on_listWidget_itemSelectionChanged();

    void XMLImport();

    void XMLExport();

    bool XMLloadfromstr(string filename);

    void viewAccount();

    void relog();

    void logNotEmpty();

    void refresh();

    void cleantext();


    void on_refresh_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_searchd_clicked();

    void on_xsearchd_clicked();

    void on_left_2_clicked();

    void on_right_2_clicked();

    void disableButtons();

    void registerUserData();



private:
    Ui::MainWindow *ui;

    void loadfrom(QString & path);
    void fillWListDino(int uid);
    void fillWListPer(int did);
    bool fileWrite(QString & path, QString & data);
    bool defaultFile(QString & path);

    void fillWListDinoSearch(int uid);

    int idofseldino();


    Storage * storage_; // <-- STORAGE
    int uid;

    int pd;
    int pp;

    bool search_mode;
    QString search_;
};

#endif // MAINWINDOW_H
