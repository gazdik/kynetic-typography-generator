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

#include <cstdio>
#include <iostream>
using namespace std;

static GLint vertexCoordAttribute;
static GLint vertexNormalAttribute;
static GLint vertexOffsetUniform;
static GLint mvpUniform;

static float seconds = 0;
static int frames = 0;

char myString[4096] = "Kiňěťíč Ťýpógráphy Gěneratoř";

const float OX = -270;
const float OY = 40;

static GLView *glView;
static GLProgram *program;
static Triangle *triangle1, *triangle2;

// FTGL vars
static FTFont *font;
FTSimpleLayout simpleLayout;

static const char vs_source[] =
{
"#version 330                                                   \n"
"                                                               \n"
"uniform mat4 mvp;                                              \n"
"uniform vec3 pen;                                              \n"
"                                                               \n"
"in      vec3 v_coord;                                        \n"
"in      vec3 v_normal;                                         \n"
"out     vec3 f_color;                                          \n"
"                                                               \n"
"void main(void) {                                              \n"
"  gl_Position = mvp * (vec4(v_coord, 1.0) + vec4(pen, 1.0)); \n"
// "  f_color = vec3(-v_coord.z/100,0.4,0.9);                    \n"
//"  f_color = vec3((v_normal.x+0.5)/2,(v_normal.y+0.5)/2,(v_normal.z+0.5)/2);  \n"
//"  f_color = vec3((v_normal.x)*0.1,(v_normal.y)*0.1,(v_normal.z)*0.1);  \n"
"  f_color = vec3(0.0f, 0.0f, 0.0f) + v_normal * 0.1;  \n"
"}                                                              \n"
};

static const char fs_source[] =
{
"#version 330                                                   \n"
"                                                               \n"
"in      vec3 f_color;                                          \n"
"out     vec4 fragColor;                                        \n"
"                                                               \n"
"void main(void) {                                              \n"
"  fragColor = vec4(f_color.x, f_color.y, f_color.z, 1.0);      \n"
"}                                                              \n"
};

static void RenderScene(void)
{
    glfwPollEvents();
    float now = glfwGetTime();

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    ActionManager::getInstance()->update(now);

    glm::mat4 projection = glm::ortho(0.0f, (float) glView->getWidth(), 0.0f, (float) glView->getHeight(), -10.0f, 100.0f);

    // Render font (transformation doesn't work!)
    program->use();
    program->setUniformMatrix4fv(mvpUniform, glm::value_ptr(projection), 1);
    simpleLayout.Render(myString, -1, FTPoint(), FTGL::RENDER_FRONT);

    triangle1->render(projection);

    glView->swapBuffers();

    frames++;

    if(now - seconds > 1.0)
    {
        fprintf(stdout, "%i FPS\n",
                frames);
        frames = 0;
        seconds += 1.0;
    }
}

int main(int argc, char **argv)
{
    char const *file = "fonts/DejaVuSerif-Bold.ttf";

    glView = new GLView("KyneTypoGen", 800, 600);
    GLFWwindow *window = glView->getWindow();

    program = new GLProgram(vs_source, fs_source);
    vertexCoordAttribute = program->getAttribLocation("v_coord");
    vertexNormalAttribute = program->getAttribLocation("v_normal");
    mvpUniform = program->getUniformLocation("mvp");
    vertexOffsetUniform = program->getUniformLocation("pen");

    triangle1 = new Triangle();
    triangle1->setContentSize(100.0f, 100.0f);
    triangle1->setPosition(100, 100);
    triangle1->setRotation(-45.0f);
    triangle1->setColor(0.99, 0.26, 0.6);

    triangle2 = new Triangle();
    triangle2->setContentSize(50.0f, 50.0f);
    triangle2->setPosition(0.0f, 75.0f);
    triangle2->setColor(0.99, 0.7, 0.1);
    triangle2->setAlpha(0.0f);
    triangle2->runAction(new FadeIn(2.0f));
    triangle2->runAction(new RotateTo(2.0f, 360.0f));
    triangle2->runAction(new ScaleTo(2.0f, 3.0f, 3.0f));

    triangle1->addChild(triangle2);
    triangle1->setAlpha(1.0f);
    triangle1->runAction(new FadeOut(2.0f));
    triangle1->runAction(new MoveTo(2.0f, glm::vec2(400.0f, 400.0f)));
    triangle1->runAction(new RotateTo(2.0f, 360.0f));

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialise FTGL stuff
    font = new FTExtrudeFont(file);

    if(font->Error())
    {
        fprintf(stderr, "%s: could not load font `%s'\n", argv[0], file);
        return EXIT_FAILURE;
    }

    font->ShaderLocations(vertexCoordAttribute, vertexNormalAttribute, vertexOffsetUniform);
    font->FaceSize(90);
    font->Depth(3);
    font->CharMap(ft_encoding_unicode);

    simpleLayout.SetFont(font);
    simpleLayout.SetLineLength(600.0f);

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
        RenderScene();
    }

    return EXIT_SUCCESS;
}
