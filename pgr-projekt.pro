TEMPLATE = app
CONFIG += console c++11 link_pkgconfig
CONFIG -= app_bundle
CONFIG -= qt
VPATH += ./src
INCLUDEPATH += ./src
PKGCONFIG += freetype2 gl glu glew ftgl

LIBS += -lglut -lGLEW -lglfw

SOURCES += effects/wordcloudeffect.cpp \
    kinetypogen.cpp \
    action.cpp\
    actionmanager.cpp \
    inputstring.cpp \
    node.cpp \
    sequencerunner.cpp \
    GLProgram.cpp \
    GLView.cpp \
    text.cpp \
    group.cpp \
    geometricshape.cpp \
    fontcache.cpp \
    effects/letteraside.cpp \
    effects/testeffect.cpp \
    effects/oneword.cpp \
    effects/rotateflyeffect.cpp \
    effects/sinkeffect.cpp

HEADERS += effects/wordcloudeffect.h \
    kinetypogen.h \
    inputstring.h \
    action.h \
    actionmanager.h \
    effect.h \
    node.h \
    sequencerunner.h \
    macros.h \
    GLProgram.h \
    GLView.h \
    text.h \
    group.h \
    geometricshape.h \
    constants.h \
    fontcache.h \
    effects/letteraside.h \
    effects/testeffect.h \
    effects/oneword.h \
    effects/rotateflyeffect.h \
    effects/sinkeffect.h
