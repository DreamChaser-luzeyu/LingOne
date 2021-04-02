QT       += core gui network core5compat testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#include(./QHotkey/qhotkey.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BitBuffer.cpp \
    QrCode.cpp \
    QrSegment.cpp \
    adbcommand.cpp \
    dialogdemo.cpp \
    firstrunwizard.cpp \
    main.cpp \
    mainmenu.cpp \
    mytcp.cpp \
    notconnectedui.cpp \
    recfile.cpp \
    scrcoysettings.cpp \
    strfunc.cpp \
    uishadow.cpp \
    widget.cpp

HEADERS += \
    BitBuffer.hpp \
    QrCode.hpp \
    QrSegment.hpp \
    adbcommand.h \
    dialogdemo.h \
    firstrunwizard.h \
    mainmenu.h \
    mytcp.h \
    notconnectedui.h \
    recfile.h \
    scrcoysettings.h \
    strfunc.h \
    uishadow.h \
    widget.h

FORMS += \
    dialogdemo.ui \
    firstrunwizard.ui \
    mainmenu.ui \
    notconnectedui.ui \
    recfile.ui \
    scrcoysettings.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    UIRes.qrc


RC_ICONS = logo.ico
