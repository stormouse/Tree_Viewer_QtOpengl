#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T15:50:45
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    material.cpp \
    objmodel.cpp \
    model.cpp \
    modelfactory.cpp \
    object.cpp \
    objectfactory.cpp \
    treeinfo.cpp \
    treeviewwidget.cpp \
    boundingbox.cpp

HEADERS  += mainwindow.h \
    material.h \
    objmodel.h \
    point3d.h \
    model.h \
    modelfactory.h \
    object.h \
    objectfactory.h \
    treeinfo.h \
    treeviewwidget.h \
    boundingbox.h

FORMS    += mainwindow.ui \
    treeviewwidget.ui

RESOURCES += \
    images.qrc
