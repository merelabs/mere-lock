QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET  = mere-lock
VERSION = 0.0.1b
TEMPLATE= app

CONFIG += c++11

DEFINES += APP_CODE=\\\"lock\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += _TESTING_

SOURCES += \
    src/config.cpp \
    src/locker.cpp \
    src/lockprompt.cpp \
    src/lockscreen.cpp \
    src/main.cpp \
    src/lockapp.cpp \
    src/screelocker.cpp \
    src/systemlocker.cpp

HEADERS += \
    src/config.h \
    src/lockapp.h \
    src/locker.h \
    src/lockprompt.h \
    src/lockscreen.h \
    src/screelocker.h \
    src/systemlocker.h

RESOURCES += \
    res/lock.qrc

DISTFILES += \
    etc/lock.conf
    share/mere-logo.png
    share/freebsd-logo.png

INCLUDEPATH += /usr/local/include

LIBS += -lX11
LIBS += -lmere-auth -lmere-config

#
# Install
#
unix
{
    target.path = /usr/local/bin

    config.path = /usr/local/etc/mere/
    config.files += etc/lock.conf

    share.path = /usr/local/share/mere/lock/
    share.files += share/mere-logo.png share/freebsd-logo.png

    INSTALLS += config share target
}

