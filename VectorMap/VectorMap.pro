TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

SOURCES += main.cpp \
    test_list_map.cpp \
    test_array.cpp \
    test_vector_map.cpp

HEADERS += \
    list_map.h \
    array.h \
    vector_map.h \
    list_map_inherit.h \
    fixed_map.h \
    binary_search.h \
    algo.h

