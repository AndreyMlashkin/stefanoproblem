#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T19:48:16
#
#-------------------------------------------------

QT       += core gui
QT       += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = displaymeltmodel
TEMPLATE = app

SOURCES += main.cpp\
           displaymeltmodel.cpp \
           meltmodel.cpp \
           deltavolume.cpp \
           meltlogics.cpp \
           meltdelegate.cpp \
           modelconstants.cpp \
           graphicswidget.cpp \
           meltview.cpp \
           stepssaver.cpp \
           array2d.cpp \
           modelfield.cpp \
           qcustomplot/qcustomplot.cpp


HEADERS  += displaymeltmodel.h \
            meltmodel.h \
            deltavolume.h \
            meltlogics.h \
            meltdelegate.h \
            modelconstants.h \
            graphicswidget.h \
            meltview.h \
            stepssaver.h \
            array2d.h \
            modelfield.h \
            qcustomplot/qcustomplot.h

FORMS    += displaymeltmodel.ui \
            graphics.ui

RESOURCES += \
    resources/resources.qrc

