#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T09:37:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQFriendsPanel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    PersonList.cpp \
    PersonListBuddy.cpp

HEADERS  += mainwindow.h \
    PersonList.h \
    PersonListBuddy.h

FORMS    += mainwindow.ui

RESOURCES += \
    resFile.qrc
