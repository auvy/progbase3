#-------------------------------------------------
#
# Project created by QtCreator 2019-06-04T23:39:50
#
#-------------------------------------------------

QT       += sql xml

TARGET = stuff
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        stuff.cpp \
    sqlite_storage.cpp \
    period.cpp \
    passhash.cpp \
    dino.cpp \
    user.cpp \

HEADERS += \
        stuff.h \
    user.h \
    storage.h \
    sqlite_storage.h \
    period.h \
    passhash.h \
    optional.h \
    dino.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
