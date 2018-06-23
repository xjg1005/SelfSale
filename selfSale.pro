#-------------------------------------------------
#
# Project created by QtCreator 2018-06-22T19:48:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = selfSale
TEMPLATE = app


SOURCES += main.cpp\
    mainweight.cpp \
    plcconnect.cpp

HEADERS  += \
    global.h \
    mainweight.h \
    plcconnect.h

FORMS    += \
    mainweight.ui
