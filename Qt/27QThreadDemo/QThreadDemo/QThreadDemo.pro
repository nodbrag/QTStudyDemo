#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T15:41:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QThreadDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Worker.cpp \
    Controller.cpp

HEADERS  += mainwindow.h \
    Worker.h \
    Controller.h

FORMS    += mainwindow.ui
