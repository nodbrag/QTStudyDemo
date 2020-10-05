#-------------------------------------------------
#
# Project created by QtCreator 2016-01-14T09:15:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoFrameDrag
TEMPLATE = app


SOURCES += main.cpp\
    FramelessWindow.cpp \
    testform.cpp

HEADERS  += \
    FramelessWindow.h \
    testform.h

FORMS    += \
    testform.ui

RESOURCES += \
    resFile.qrc
