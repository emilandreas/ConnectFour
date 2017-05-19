TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic

QMAKE_CXX = clang++

SOURCES += main.cpp \
    connectfour.cpp

HEADERS += \
    connectfour.h
