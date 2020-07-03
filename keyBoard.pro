#-------------------------------------------------
#
# Project created by QtCreator 2020-06-04T18:31:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keyBoard
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
    imagemap.cpp \
    keyconfig.cpp \
        main.cpp \
        mainwindow.cpp \
    nofocusframedelegate.cpp \
    pluginmap.cpp \
    toolsbutton.cpp \
    funtiontree.cpp \
    keytimer.cpp \
    virtualpage.cpp \
    systools.cpp \
    key_mkdir.cpp \
    treeitemdelegate.cpp \
    keyexec.cpp

HEADERS += \
    imagemap.h \
    keyconfig.h \
        mainwindow.h \
    nofocusframedelegate.h \
    pluginmap.h \
    toolsbutton.h \
    plugininterface.h \
    virtualkey.h \
    funtiontree.h \
    keytimer.h \
    virtualpage.h \
    systools.h \
    key_mkdir.h \
    treeitemdelegate.h \
    keyexec.h

FORMS += \
        mainwindow.ui \
    virtualpage.ui \
    keyexec.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
