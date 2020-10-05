#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T16:27:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpreadSheet
TEMPLATE = app


SOURCES += main.cpp\
        spreadsheet.cpp \
    Cell.cpp \
    finddialog.cpp \
    gotocelldialog.cpp \
    MainWindow.cpp \
    sortdialog.cpp

HEADERS  += spreadsheet.h \
    Cell.h \
    finddialog.h \
    gotocelldialog.h \
    MainWindow.h \
    sortdialog.h

FORMS += \
    gotocelldialog.ui \
    sortdialog.ui

RESOURCES += \
    spreadsheet.qrc
