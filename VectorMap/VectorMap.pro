TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

SOURCES += main.cpp \
    test_iterator.cpp

HEADERS += \
    list_map.h

