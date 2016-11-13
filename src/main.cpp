#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>

#define glm_force_radians
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLProgram.h>
#include <GLView.h>

#include <cstdio>
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

// FTGL vars
static FTFont *font;
FTSimpleLayout simpleLayout;

static const char vs_source[] =
{
"#version 150                                                   \n"
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
"  f_color = vec3(0.0f, 0.0f, 0.0f);  \n"
"}                                                              \n"
};

static const char fs_source[] =
{
"#version 150                                                   \n"
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

    float angle = now * 45;
    glm::vec3 axis_y(0, 1, 0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis_y);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.2, 0.3, -4.0));

    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(45.0f, 1.0f*glView->getWidth() / glView->getHeight(), 1.0f, 20.0f);

    glm::mat4 mvp = projection * view * model * scale * anim;

    program->use();
    program->setUniformMatrix4fv(mvpUniform, glm::value_ptr(mvp), 1);

//    simpleLayout.Render(myString, -1, FTPoint(), FTGL::RENDER_SIDE);
    simpleLayout.Render(myString, -1, FTPoint(), FTGL::RENDER_FRONT);

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

    glView = new GLView("KyneTypoGen", 640, 480);
    GLFWwindow *window = glView->getWindow();

    program = new GLProgram(vs_source, fs_source);
    vertexCoordAttribute = program->getAttribLocation("v_coord");
    vertexNormalAttribute = program->getAttribLocation("v_normal");
    mvpUniform = program->getUniformLocation("mvp");
    vertexOffsetUniform = program->getUniformLocation("pen");

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
//    font->Outset(1, 2);
    font->CharMap(ft_encoding_unicode);

    simpleLayout.SetFont(font);
    simpleLayout.SetLineLength(600.0f);

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
        RenderScene();
    }

    return EXIT_SUCCESS;
}
