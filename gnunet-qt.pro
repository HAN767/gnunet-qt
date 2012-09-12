#-------------------------------------------------
#
# Project created by QtCreator 2012-08-31T08:23:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gnunet-qt
TEMPLATE = app


SOURCES += main.cpp\
    about.cpp \
    preferences.cpp \
    pages.cpp \
    transferwnd.cpp \
    peerinfo.cpp \
    eventloop.cpp \
    gnunetmanager.cpp \
    cangote.cpp \
    cangoteDlg.cpp \
    networkwnd.cpp \
    gnunetnetworkpeersmodel.cpp \
    searchwnd.cpp

HEADERS  += \
    about.h \
    preferences.h \
    pages.h \
    transferwnd.h \
    peerinfo.h \
    eventloop.h \
    gnunet_includes.h \
    gnunetmanager.h \
    cangote.h \
    cangoteDlg.h \
    networkwnd.h \
    gnunetnetworkpeersmodel.h \
    gnunetincludes.h \
    gnunet_definitions.h \
    searchwnd.h

FORMS    += \
    about.ui \
    cangoteDlg.ui

OTHER_FILES += \
    images/update.png \
    images/query.png \
    images/config.png

RESOURCES += \
    preferences.qrc

INCLUDEPATH += gnunet

LIBS += -lgnunetutil -lgnunetfs -lgnunetpeerinfo -lgnunetcore -lgnunettransport -lgnunetats -l ws2_32
