#-------------------------------------------------
#
# Project created by QtCreator 2024-04-16T07:07:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Alarm
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
        main.cpp \
        mainwindow.cpp \
    alarm.cpp \
    telegram.cpp \
    telegram2.cpp

HEADERS += \
        mainwindow.h \
    alarm.h \
    HCNetSDK.h \
    telegram.h \
    telegram2.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH += $$PWD/HCNetSDK.h

LIBS +=/etc/telegram/librerias/libhcnetsdk.so
LIBS +=/etc/telegram/librerias/libhpr.so
LIBS +=/etc/telegram/librerias/libHCCore.so
LIBS +=/etc/telegram/librerias/libz.so
LIBS +=/etc/telegram/librerias/libSuperRender.so
LIBS +=/etc/telegram/librerias/libssl.so.1.1
LIBS +=/etc/telegram/librerias/libPlayCtrl.so
LIBS +=/etc/telegram/librerias/libopenal.so.1
LIBS +=/etc/telegram/librerias/libNPQos.so
LIBS +=/etc/telegram/librerias/libcrypto.so.1.1
LIBS +=/etc/telegram/librerias/libAudioRender.so
