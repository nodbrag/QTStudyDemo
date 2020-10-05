#-------------------------------------------------
#
# Project created by QtCreator 2020-05-04T22:30:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditorDelegate
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
        delegate/PersistentStyledItemDelegate.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        delegate/ButtonDelegate.h \
        delegate/DateTimeEditDelegate.h \
        delegate/PersistentStyledItemDelegate.h \
        delegate\ComboBoxDelegate.h \
        delegate\IconDelegate.h \
        delegate\LineEditDelegate.h \
        delegate\ProgressBarDelegate.h \
        delegate\ReadOnlyDelegate.h \
        delegate\SpinBoxDelegate.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += . \
               delegate

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
