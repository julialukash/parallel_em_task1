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


unix:QMAKE_CXXFLAGS += -fopenmp
else:macx:QMAKE_CXXFLAGS += -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.8

unix:QMAKE_LFLAGS += -fopenmp
else:macx:QMAKE_CFLAGS += -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.8

unix:CONFIG += c++11
else:macx:CONFIG += c++14

macx:
{
    LIBS += -L"/usr/local/Cellar/boost/1.61.0_1/lib"
    INCLUDEPATH += "/usr/local/Cellar/boost/1.61.0_1/include"
}

SOURCES += main.cpp \
    em_algo.cpp \
    model.cpp


HEADERS += \
    em_algo.h \
    interface.h \
    model.h
