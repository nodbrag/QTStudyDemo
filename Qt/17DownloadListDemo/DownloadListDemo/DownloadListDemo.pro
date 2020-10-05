#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T10:30:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DownloadListDemo
TEMPLATE = app


SOURCES += main.cpp\
        DownloadListDemo.cpp \
    DownloadListConfig.cpp \
    tinyXml/tinystr.cpp \
    tinyXml/tinyxml.cpp \
    tinyXml/tinyxmlerror.cpp \
    tinyXml/tinyxmlparser.cpp

HEADERS  += DownloadListDemo.h \
    DownloadListConfig.h \
    tinyXml/tinystr.h \
    tinyXml/tinyxml.h

FORMS    += DownloadListDemo.ui
