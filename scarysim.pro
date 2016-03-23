#-------------------------------------------------
#
# Project created by QtCreator 2011-10-02T21:14:46
#
#-------------------------------------------------

QT       += core gui\
            opengl\
            widgets

LIBS     += -lglut -lGLU

TARGET = scarysim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    model.cpp \
    scara.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    model.h \
    scara.h

FORMS    += mainwindow.ui






