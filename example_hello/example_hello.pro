#-------------------------------------------------
#
# Project created by QtCreator 2016-09-24T16:52:47
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = example1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS+=-fopenmp
QMAKE_LFLAGS += -fopenmp

SOURCES += main.cpp
