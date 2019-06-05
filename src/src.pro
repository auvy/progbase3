#-------------------------------------------------
#
# Project created by QtCreator 2019-05-01T20:54:04
#
#-------------------------------------------------

QT       += core gui
QT += xml
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab9
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


LIBS += -L/home/auvy/Desktop/fsgdg/src/lib/stuff -lstuff
INCLUDEPATH +=/home/auvy/Desktop/fsgdg/src/lib

SUBDIRS += \
    lab9.pro

FORMS += \
    add_d.ui \
    edit_d.ui \
    edit_p.ui \
    mainwindow.ui \
    auth.ui \
    usermenu.ui \
    change_pass.ui \
    change_name.ui \
    createacc.ui \
    create_p.ui

DISTFILES += \
    sql/data.sqlite \
    data.sqlite \
    sqldata.sqlite

HEADERS += \
    add_d.h \
    edit_d.h \
    edit_p.h \
    mainwindow.h \
    auth.h \
    usermenu.h \
    change_pass.h \
    change_name.h \
    createacc.h \
    create_p.h

SOURCES += \
    add_d.cpp \
    edit_d.cpp \
    edit_p.cpp \
    main.cpp \
    mainwindow.cpp \
    auth.cpp \
    usermenu.cpp \
    change_pass.cpp \
    change_name.cpp \
    createacc.cpp \
    create_p.cpp
