TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglut

SOURCES += main.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += freetype2 gl glu ftgl
