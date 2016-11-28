TEMPLATE = app
CONFIG += console c++11 link_pkgconfig
CONFIG -= app_bundle
CONFIG -= qt
VPATH += ./src
INCLUDEPATH += ./src
PKGCONFIG += freetype2 gl glu glew ftgl

LIBS += -lglut -lGLEW -lglfw

SOURCES += kinetypogen.cpp \
    action.cpp\
    actionmanager.cpp \
    inputstring.cpp \
    node.cpp \
    sequencerunner.cpp \
    testeffect.cpp \
    GLProgram.cpp \
    GLView.cpp \
    text.cpp \
    group.cpp \
    geometricshape.cpp

HEADERS += kinetypogen.h \
    inputstring.h \
    action.h \
    actionmanager.h \
    effect.h \
    node.h \
    sequencerunner.h \
    testeffect.h \
    macros.h \
    GLProgram.h \
    GLView.h \
    text.h \
    group.h \
    geometricshape.h \
    constants.h
