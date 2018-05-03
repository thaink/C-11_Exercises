TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

SOURCES += main.cpp \
    test_list_map.cpp \
    test_array.cpp

HEADERS += \
    list_map.h \
    array.h

