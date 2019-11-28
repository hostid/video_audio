#-------------------------------------------------
#
# Project created by QtCreator 2017-05 沙振宇
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo_Vlc
TEMPLATE = app

#添加相关库

INCLUDEPATH += $$PWD/vlc_win32/include/
INCLUDEPATH += $$PWD/vlc_win32/include/vlc/
LIBS += -L$$PWD/vlc_win32
LIBS += -llibvlc -llibvlccore

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
