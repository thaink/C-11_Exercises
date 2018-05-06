TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    interval_map.cpp \
    main.cpp

HEADERS += \
    interval_map.h

