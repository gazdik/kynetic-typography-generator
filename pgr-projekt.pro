TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lglut

SOURCES += main.cpp \
    inputstring.cpp \
    node.cpp \
    sequencerunner.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += freetype2 gl glu ftgl

HEADERS += \
    inputstring.h \
    effect.h \
    node.h \
    sequencerunner.h
