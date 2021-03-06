#-------------------------------------------------
#
# Project created by QtCreator 2018-05-03T15:06:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt5warm
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += model qt5

SOURCES +=\
    model/src/Point.cpp \
    model/src/Way.cpp \
    model/src/RabbitFactory.cpp \
    model/src/Rabbit.cpp \
    model/src/GraphicSnake.cpp \
    model/src/GraphicPoint.cpp \
    model/src/Model.cpp \
    model/src/Control.cpp \
    qt5/src/Qt5View.cpp \
    qt5/src/MainWindow.cpp \
    qt5/src/main.cpp

HEADERS  += \
    model/version.h \
    model/Point.h \
    model/Way.h \
    model/ISnake.h \
    model/TSnake.h \
    model/IModel.h \
    model/Model.h \
    model/IControl.h \
    model/Control.h \
    model/IView.h \
    model/Rabbit.h \
    model/RabbitFactory.h \
    model/GraphicPoint.h \
    model/GraphicSnake.h \
    qt5/Qt5View.h \
    qt5/MainWindow.h \
    qt5/Qt5Version.h \
    model/TGraphicView.h
