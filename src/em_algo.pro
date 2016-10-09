#-------------------------------------------------
#
# Project created by QtCreator 2016-09-24T16:52:47
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = em_algo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

macx:QMAKE_CXXFLAGS += -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.10
else:unix:QMAKE_CXXFLAGS += -fopenmp

macx:QMAKE_CFLAGS += -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.10
else:unix:QMAKE_LFLAGS += -fopenmp

macx:CONFIG += c++14
else:unix:CONFIG += c++11

macx:LIBS += -L"/usr/local/Cellar/boost/1.61.0_1/lib"
else:LIBS += -L"~/parallel/task1/papi-5.5.0/src/libpfm4/lib" -lpapi

macx:INCLUDEPATH += "/usr/local/Cellar/boost/1.61.0_1/include"
else:INCLUDEPATH += "~/parallel/task1/papi-5.5.0/src/libpfm4/include"

SOURCES += main.cpp \
    em_algo.cpp \
    model.cpp \
    import_data.cpp


HEADERS += \
    em_algo.h \
    interface.h \
    model.h \
    import_data.h
