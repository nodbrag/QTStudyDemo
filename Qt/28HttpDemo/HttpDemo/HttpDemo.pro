#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T23:00:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HttpDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkcookie.cpp \
    BaseHandler.cpp

HEADERS  += mainwindow.h \
    networkcookie.h \
    BaseHandler.h

FORMS    += mainwindow.ui
