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
    bodyiterator.cpp \
    simulationcluster.cpp \
    clusterbodybuilder.cpp

HEADERS  += dialog.h \
    body.h \
    debug.h \
    config_keyvalue.h \
    config.h \
    config_section.h \
    prototype.h \
    planetary_bodybuilder.h \
    bodybuilder.h \
    simulationfacade.h \
    bodyiterator.h \
    simulationcluster.h \
    simulationobject.h \
    clusterbodybuilder.h

FORMS    += dialog.ui