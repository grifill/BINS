#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T16:57:03
#
#-------------------------------------------------


QT       += core gui\
            printsupport

QT       += serialport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FG_Bins
TEMPLATE = app
DESTDIR = ./../application

VERSION= 0.0.1
QMAKE_TARGET_COMPANY= FGU
QMAKE_TARGET_PRODUCT= FG_Bins
QMAKE_TARGET_DESCRIPTION= FG_Bins
QMAKE_TARGET_COPYRIGHT= Filatov Grigoriy


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    inc/glwidget.h \
    glwidget.h

FORMS    += mainwindow.ui

RC_FILE=file.rc
RESOURCES += pic.qrc
