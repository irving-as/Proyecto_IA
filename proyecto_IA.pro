#-------------------------------------------------
#
# Project created by QtCreator 2016-05-12T11:47:36
#
#-------------------------------------------------

QT       += core gui
QT += widgets
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyecto_IA
TEMPLATE = app

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_ml -lopencv_imgproc


SOURCES += main.cpp\
        mainwindow.cpp \
    mywidget.cpp \
    childwindow.cpp \
    network.cpp

HEADERS  += mainwindow.h \
    mywidget.h \
    childwindow.h \
    network.h

FORMS    += mainwindow.ui \
    mywidget.ui
