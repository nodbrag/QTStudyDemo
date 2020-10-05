#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T15:43:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQTooTip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MessageTipForm.cpp \
    SystemTrayIcon.cpp

HEADERS  += mainwindow.h \
    MessageTipForm.h \
    SystemTrayIcon.h

FORMS    += mainwindow.ui \
    MessageTipForm.ui

RESOURCES += \
    resFile.qrc
