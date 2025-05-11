#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T12:02:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SynthSwitch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qsynthswitch.cpp

HEADERS  += mainwindow.h \
    qsynthswitch.h

FORMS    += mainwindow.ui

RESOURCES += \
    synthswitchresources.qrc

DISTFILES += \
    QSynthSwitch.pri
