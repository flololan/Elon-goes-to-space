#-------------------------------------------------
#
# Project created by QtCreator 2022-01-22T20:41:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ElonGoesToSpace
TEMPLATE = app

#Path to .h-Files of IFC
INCLUDEPATH += "C:\Program Files\Immersion Corporation\IFC23\inc"
#Adding the IFC library
LIBS += "C:\Program Files\Immersion Corporation\IFC23\lib\IFC23.lib"


SOURCES += main.cpp\
        mainwindow.cpp \
    hapticcontroller.cpp

HEADERS  += mainwindow.h \
    hapticcontroller.h

FORMS    += mainwindow.ui
