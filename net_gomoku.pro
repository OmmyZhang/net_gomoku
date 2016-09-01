#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T16:43:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = net_gomoku
TEMPLATE = app


SOURCES += main.cpp \
    begin.cpp \
    switchcontrol.cpp \
    mainbody.cpp

HEADERS  += \
    begin.h \
    switchcontrol.h \
    mainbody.h

FORMS    += \
    begin.ui
