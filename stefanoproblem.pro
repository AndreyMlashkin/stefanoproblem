#-------------------------------------------------
#
# Project created by QtCreator 2013-07-09T21:10:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stefanoproblem
TEMPLATE = app


SOURCES += main.cpp\
    displaymeltmodel.cpp \
    meltmodel.cpp \
    deltavolume.cpp \
    field.cpp \
    meltlogics.cpp \
    meltdelegate.cpp

HEADERS  += \
    displaymeltmodel.h \
    meltmodel.h \
    deltavolume.h \
    field.h \
    meltlogics.h \
    meltdelegate.h

FORMS    += \
    displaymeltmodel.ui
