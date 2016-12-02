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

#include <math.h>

#include <GLProgram.h>
#include <GLView.h>
#include "group.h"
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
#include "effects/wordcloudeffect.h"
#include "effects/testeffect.h"
#include "effects/letteraside.h"
#include "effects/oneword.h"
#include "effects/calibrationeffect.h"
#include "effects/rotateflyeffect.h"
#include "effects/sinkeffect.h"

class KineTypoGen
{
public:
    KineTypoGen(int& argc, char* argv[]);
    ~KineTypoGen();
    int run();
private:
    void renderScene();
    void readOptions(int& argc, char* argv[]);

    // The only FTGL variable...
    static const char fontFile[];

    float seconds = 0;
    int frames = 0;

    GLView *glView;

    Group *mainNode;

    int seed;
    std::string str;
    float previoutTime;
};

#endif // KINETYPOGEN_H
