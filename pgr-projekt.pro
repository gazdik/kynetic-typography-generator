TEMPLATE = app
CONFIG += console c++11 link_pkgconfig
CONFIG -= app_bundle
CONFIG -= qt
PKGCONFIG += freetype2 gl glu ftgl

LIBS += -lglut

SOURCES += main.cpp \
    inputstring.cpp \
    node.cpp \
    sequencerunner.cpp \
    testeffect.cpp \
    kinetypogen.cpp

HEADERS += \
    inputstring.h \
    effect.h \
    node.h \
    sequencerunner.h \
    testeffect.h \
    kinetypogen.h
