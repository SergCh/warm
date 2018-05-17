#-------------------------------------------------
#
# Project created by QtCreator 2018-05-03T15:06:40
#
#-------------------------------------------------

TARGET = cursesworm
TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle

INCLUDEPATH += model curses
LIBS += -lncurses


SOURCES +=\
    model/src/Point.cpp \
    model/src/Way.cpp \
    model/src/RabbitFactory.cpp \
    model/src/Rabbit.cpp \
    model/src/Model.cpp \
    model/src/Control.cpp \
    curses/src/CursesView.cpp \
    curses/main.cpp

HEADERS  += \
    model/version.h \
    model/Point.h \
    model/Way.h \
    model/ISnake.h \
    model/TSnake.h \
    model/TSnake.tcc \
    model/IModel.h \
    model/Model.h \
    model/IControl.h \
    model/Control.h \
    model/IView.h \
    model/Rabbit.h \
    model/RabbitFactory.h \
    curses/CursesView.h \
    curses/CursesVersion.h

