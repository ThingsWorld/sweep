#-------------------------------------------------
#
# Project created by QtCreator 2017-01-11T09:59:11
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sweep
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sweepitem.cpp \
    data.cpp \
    sweepscene.cpp \
    sweepview.cpp

HEADERS  += mainwindow.h \
    sweepitem.h \
    data.h \
    sweepscene.h \
    sweepview.h

RESOURCES += \
    pic.qrc
