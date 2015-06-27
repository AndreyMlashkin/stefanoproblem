
QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = displaymeltmodel
TEMPLATE = app

UI_DIR = ./tmp/ui
MOC_DIR = ./tmp/moc
RCC_DIR = ./tmp/rcc

CONFIG( debug, debug|release ) {

    __LIBS_DIR              =   bin/debug
    OBJECTS_DIR             +=  tmp/obj/debug

} else {

    __LIBS_DIR              =   bin/release
    OBJECTS_DIR             +=  tmp/obj/release
}

DESTDIR = $$__LIBS_DIR

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
           modelfield.cpp \
           qcustomplot/qcustomplot.cpp \
    languagechooser.cpp


HEADERS  += displaymeltmodel.h \
            meltmodel.h \
            deltavolume.h \
            meltlogics.h \
            meltdelegate.h \
            modelconstants.h \
            graphicswidget.h \
            meltview.h \
            stepssaver.h \
            modelfield.h \
            array2d/array2d.h \
            array2d/arrayiterator.h \
            qcustomplot/qcustomplot.h \
            modelapi.h \
    languagechooser.h

FORMS    += displaymeltmodel.ui \
            graphics.ui

RESOURCES += \
    resources/resources.qrc


TRANSLATIONS = translation_de.ts \
               translation_en.ts

