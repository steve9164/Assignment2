#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T17:12:52
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = assignment-part1
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    body.cpp \
    config.cpp \
    config_section.cpp \
    config_keyvalue.cpp \
    planetary_bodybuilder.cpp \
    simulationfacade.cpp \
    objectprototype.cpp \
    bodyiterator.cpp \
    clusterbuilder.cpp \
    cluster.cpp \
    bodybuilder.cpp \
    listobjects.cpp

HEADERS  += dialog.h \
    body.h \
    debug.h \
    config_keyvalue.h \
    config.h \
    config_section.h \
    planetary_bodybuilder.h \
    bodybuilder.h \
    simulationfacade.h \
    objectprototype.h \
    bodyiterator.h \
    clusterbuilder.h \
    cluster.h \
    listobjects.h

FORMS    += dialog.ui \
    listobjects.ui
