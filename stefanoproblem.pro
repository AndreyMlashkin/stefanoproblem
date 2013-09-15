#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T19:48:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = displaymeltmodel
TEMPLATE = app

SOURCES += main.cpp\
           displaymeltmodel.cpp \
           meltmodel.cpp \
           deltavolume.cpp \
           field.cpp \
           meltlogics.cpp \
           meltdelegate.cpp \
           modelconstants.cpp \
           graphicswidget.cpp \
           meltview.cpp \
           stepssaver.cpp

HEADERS  += displaymeltmodel.h \
            meltmodel.h \
            deltavolume.h \
            field.h \
            meltlogics.h \
            meltdelegate.h \
            modelconstants.h \
            graphicswidget.h \
            meltview.h \
            stepssaver.h

FORMS    += displaymeltmodel.ui \
            graphics.ui

CONFIG   += qwtconfig
