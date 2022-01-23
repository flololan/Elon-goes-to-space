#-------------------------------------------------
#
# Project created by Johann and Florian
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
    hapticcontroller.cpp \
    scenes.cpp \
    scene.cpp \
    hapticeffect.cpp \
    effect.cpp \
    helper.cpp

HEADERS  += mainwindow.h \
    hapticcontroller.h \
    scenes.h \
    scene.h \
    hapticeffect.h \
    effect.h \
    helper.h \
    effecttype.h

FORMS    += mainwindow.ui

RESOURCES += \
                assets.qrc

DISTFILES += \
    ../../assets/draggableItems/asset_tiny_elon.png
