QT       += core gui network core5compat concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adbcommand.cpp \
    connectdev.cpp \
    main.cpp \
    mainmenu.cpp \
    mytcp.cpp \
    receivefile.cpp \
    receivetext.cpp \
    settings.cpp \
    uishadow.cpp

HEADERS += \
    adbcommand.h \
    connectdev.h \
    mainmenu.h \
    mytcp.h \
    receivefile.h \
    receivetext.h \
    settings.h \
    uishadow.h

FORMS += \
    connectdev.ui \
    mainmenu.ui \
    receivefile.ui \
    receivetext.ui \
    settings.ui

TRANSLATIONS += \
    Bind_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    UIres.qrc
