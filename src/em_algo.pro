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

unix:
{
    #QMAKE_CXXFLAGS += -fopenmp
    #QMAKE_LFLAGS += -fopenmp
    CONFIG += c++11
}

macx:
{
    QMAKE_CXXFLAGS += -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.8
    QMAKE_CFLAGS += -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.8
    CONFIG += c++14

    LIBS += -L"/usr/local/Cellar/boost/1.61.0_1/lib"
    INCLUDEPATH += "/usr/local/Cellar/boost/1.61.0_1/include"
}

SOURCES += main.cpp \
    em_algo.cpp


HEADERS += \
    em_algo.h \
    interface.h
