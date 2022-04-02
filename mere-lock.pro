QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET  = mere-lock
VERSION = 0.0.1b
TEMPLATE= app

CONFIG += c++11
#CONFIG += debug_and_release

DEFINES += APP_CODE=\\\"lock\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES += \
    src/config.cpp \
    src/locker.cpp \
    src/lockprompt.cpp \
    src/lockscreen.cpp \
    src/main.cpp \
    src/lockapp.cpp \
    src/screenlocker.cpp \
    src/systemlocker.cpp

HEADERS += \
    src/config.h \
    src/lockapp.h \
    src/locker.h \
    src/lockprompt.h \
    src/lockscreen.h \
    src/screenlocker.h \
    src/systemlocker.h

RESOURCES += \
    res/lock.qrc

DISTFILES += \
    etc/lock.conf
    share/mere-logo.png
    share/freebsd-logo.png

TRANSLATIONS += \
    i18n/lock_bn.ts \
    i18n/lock_en.ts

OTHER_FILES += \
    README.md


INCLUDEPATH += /usr/local/include

LIBS += -lX11
LIBS += -lmere-auth -lmere-config-lite -lmere-utils -lmere-widgets

##
## TS file(s)
##
#qtPrepareTool(LUPDATE, lupdate)
#command = $$LUPDATE mere-lock.pro
#system($$command)|error("Failed to run: $$command")

#
# Generate QM file(s) from TS file(s)
#
qtPrepareTool(LRELEASE, lrelease)
command = $$LRELEASE -removeidentical i18n/*.ts
system($$command)|error("Failed to run: $$command")

#
# Install
#
unix
{
    pre.path = $${OUT_PWD}/build
    pre.commands = echo pre-install > /dev/null
    #pre.depends =

    INSTALLS += pre

    target.path = /usr/local/bin

    i18n.path = /usr/local/share/mere/lock/i18n
    i18n.files = i18n/*.qm

    desktop.path  = /usr/local/share/applications/
    desktop.files = mere-lock.desktop

    config.path = /usr/local/etc/mere/
    config.files += etc/lock.conf

    share.path = /usr/local/share/mere/lock/
    share.files += share/mere-logo.png share/freebsd-logo.png

    INSTALLS += config share i18n desktop target

    !linux-g++ {
        post.path = $${OUT_PWD}/build
        post.commands = chmod u+s /usr/local/bin/mere-lock
        #post.depends =

        INSTALLS += post
    }
}
