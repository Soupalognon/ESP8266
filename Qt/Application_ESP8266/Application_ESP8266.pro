#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T00:33:04
#
#-------------------------------------------------

QT       += core gui

include(G:\Qt\Tools\QtCreator\lib\qextserialport-1.2rc\src\qextserialport.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Application_ESP8266
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
