#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T18:42:28
# Author: Nauroze Hoath
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = objectTracking2
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        camaraConfig.cpp \
        video/mainvideocapture.cpp

HEADERS  += \
    camaraConfig.h \
    video/mainvideocapture.h

FORMS    += \
    camaraConfig.ui

INCLUDEPATH += 'pkg-config --cflags opencv'
LIBS        += `pkg-config --libs opencv`



