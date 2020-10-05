QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Test1\
               Test2 \
               Test3

SOURCES += \
        Test1/Test1.cpp \
        Test2/Test2.cpp \
        Test3/Test3.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Test1/Test1.h \
    Test2/ISysInfo.h \
    Test2/SysInfoLinux.h \
    Test2/SysInfoWin.h \
    Test2/Test2.h \
    Test3/Test3.h

# for test3
win32 {
    HEADERS += Test3/win/SysInfo.h
    INCLUDEPATH += Test3/win
} else {
    HEADERS += Test3/linux/SysInfo.h
    INCLUDEPATH += Test3/linux
}
