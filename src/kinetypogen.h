#ifndef KINETYPOGEN_H
#define KINETYPOGEN_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLProgram.h>
#include <GLView.h>
#include "triangle.h"
#include "actionmanager.h"
#include "action.h"

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <sstream>
#include <streambuf>
#include <string>

#include "sequencerunner.h"
#include "effect.h"

// Effects
#include "testeffect.h"

class KineTypoGen
{
public:
    KineTypoGen(int& argc, char* argv[]);
    int run();
private:
    void renderScene();
    void readOptions(int& argc, char* argv[]);

    static const char fontFile[];
    static const char vsSource[];
    static const char fsSource[];
    static const float OX;
    static const float OY;

    GLint vertexCoordAttribute;
    GLint vertexNormalAttribute;
    GLint vertexOffsetUniform;
    GLint mvpUniform;

    float seconds = 0;
    int frames = 0;

    GLView *glView;
    GLProgram *program;

    // TODO: Replace with a normal container
    //static Node *mainNode;
    Triangle *mainNode;

    // FTGL vars
    FTFont *font;
    FTSimpleLayout simpleLayout;

    int seed;
    std::string str;
};

#endif // KINETYPOGEN_H
