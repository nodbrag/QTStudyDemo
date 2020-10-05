QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

#BOOST默认使用静态链接方式，所以使用这个宏，定义使用动态链接方式。
DEFINES += BOOST_ALL_DYN_LINK=1

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

#包含boost头文件
INCLUDEPATH += C:/Boost_msvc_shared/include/boost-1_71

#包含boost动态库路径，不需要加-lxxx。因为使用boost的auto link机制。
LIBS += -LC:/Boost_msvc_shared/lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
