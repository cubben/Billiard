#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Billiard
TEMPLATE = app
LIBS    += -lOpengl32

SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    table.cpp \
    kugel.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    table.h \
    kugel.h

FORMS    += mainwindow.ui
