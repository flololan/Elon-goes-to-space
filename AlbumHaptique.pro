#-------------------------------------------------
#
# Project created by QtCreator 2018-02-10T14:47:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlbumHaptique
TEMPLATE = app

INCLUDEPATH += "C:\Program Files\Immersion Corporation\IFC23\inc"

LIBS += "C:\Program Files\Immersion Corporation\IFC23\lib\IFC23.lib"

SOURCES += main.cpp\
        mainwindow.cpp \
    album.cpp \
    page.cpp \
    gestionhaptique.cpp \
    pagevibration.cpp \
    vibration.cpp \
    util.cpp

HEADERS  += mainwindow.h \
    album.h \
    page.h \
    gestionhaptique.h \
    pagevibration.h \
    vibration.h \
    util.h \
    vibrationtype.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    ../../Desktop/bonhomme.png
	

