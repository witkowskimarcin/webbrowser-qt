#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T12:11:33
#
#-------------------------------------------------

QT += core gui webengine webenginewidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = web2
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    favouritedialog.cpp \
    favourite.cpp \
    addfavouritedialog.cpp \
    page.cpp \
    historyitem.cpp \
    historydialog.cpp \
    sourcecodedialog.cpp \
    highlighter.cpp \
    savelinkdialog.cpp

HEADERS += \
        mainwindow.h \
    favouritedialog.h \
    favourite.h \
    addfavouritedialog.h \
    page.h \
    historyitem.h \
    historydialog.h \
    sourcecodedialog.h \
    highlighter.h \
    savelinkdialog.h

FORMS += \
        mainwindow.ui \
    favouritedialog.ui \
    addfavouritedialog.ui \
    historydialog.ui \
    sourcecodedialog.ui \
    savelinkdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
