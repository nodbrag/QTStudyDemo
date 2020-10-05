#-------------------------------------------------
#
# Project created by QtCreator 2018-01-13T11:38:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebQQ
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    BaseHandler.cpp \
    QRCodeHandler.cpp \
    LoginDialog.cpp \
    LoginHandler.cpp

HEADERS  += mainwindow.h \
    BaseHandler.h \
    QRCodeHandler.h \
    LoginDialog.h \
    LoginHandler.h

FORMS    += mainwindow.ui \
    LoginDialog.ui
