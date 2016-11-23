#include "kinetypogen.h"

const char KineTypoGen::fontFile[] = "fonts/DejaVuSerif-Bold.ttf";
const float OX = -270.0f;
const float OY = 40.0f;

const char KineTypoGen::vsSource[] =
{
"#version 330                                                   \n"
"                                                               \n"
"uniform mat4 mvp;                                              \n"
"uniform vec3 pen;                                              \n"
"                                                               \n"
"in      vec3 v_coord;                                          \n"
"in      vec3 v_normal;                                         \n"
"out     vec3 f_color;                                          \n"
"                                                               \n"
"void main(void) {                                              \n"
"  gl_Position = mvp * (vec4(v_coord, 1.0) + vec4(pen, 1.0));   \n"
//"  f_color = vec3(-v_coord.z/100,0.4,0.9);                    \n"
//"  f_color = vec3((v_normal.x+0.5)/2,(v_normal.y+0.5)/2,(v_normal.z+0.5)/2);  \n"
//"  f_color = vec3((v_normal.x)*0.1,(v_normal.y)*0.1,(v_normal.z)*0.1);  \n"
"  f_color = vec3(0.0f, 0.0f, 0.0f) + v_normal * 0.1;           \n"
"}                                                              \n"
};

const char KineTypoGen::fsSource[] =
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

void KineTypoGen::readOptions(int& argc, char* argv[])
{
    if (argc > 2 && strcmp(argv[1], "-s") == 0) {
        seed = atoi(argv[2]);
        argc -= 2;
        argv = &argv[2];
    } else {
        seed = time(NULL);
    }

    if (argc > 1) {
        std::ifstream fr(argv[1]);
        if (!fr) {
            throw std::runtime_error("Cannot open specified text file.");
        }
        str.assign(std::istreambuf_iterator<char>(fr),
                   std::istreambuf_iterator<char>());
    } else {
        str.assign(std::istream_iterator<char>(std::cin),
                   std::istream_iterator<char>());
    }
}

KineTypoGen::KineTypoGen(int& argc, char* argv[])
{
    readOptions(argc, argv);

    glView = new GLView("KineTypoGen", 800, 600);


    program = new GLProgram(vsSource, fsSource);
    vertexCoordAttribute = program->getAttribLocation("v_coord");
    vertexNormalAttribute = program->getAttribLocation("v_normal");
    mvpUniform = program->getUniformLocation("mvp");
    vertexOffsetUniform = program->getUniformLocation("pen");

    // TODO: Replace with a normal container
    //mainNode = new Node();
    mainNode = new Triangle();
    mainNode->setContentSize(100.0f, 100.0f);

    // Do the magic here

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialise FTGL stuff
    font = new FTExtrudeFont(fontFile);

    if(font->Error())
    {
        std::ostringstream ss;
        ss << "Could not load font '" << fontFile << "'" << std::endl;
        throw new std::runtime_error(ss.str());
    }

    font->ShaderLocations(vertexCoordAttribute, vertexNormalAttribute, vertexOffsetUniform);
    font->FaceSize(90);
    font->Depth(3);
    font->CharMap(ft_encoding_unicode);

    simpleLayout.SetFont(font);
    simpleLayout.SetLineLength(600.0f);
}

int KineTypoGen::run()
{
    std::vector<Effect*> effects;
    effects.push_back(new TestEffect());
    // effects declarations go here

    SequenceRunner sequenceRunner(effects);
    std::cout << "Seed: " << seed << std::endl;
    sequenceRunner.run(str, seed, *mainNode);

    GLFWwindow *window = glView->getWindow();
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {
        renderScene();
    }

    for (Effect* effect : effects) {
        delete(effect);
    }
    return 0;
}

void KineTypoGen::renderScene()
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
    simpleLayout.Render(str.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT);

    mainNode->render(projection);

    glView->swapBuffers();

    frames++;

    if(now - seconds > 1.0)
    {
        std::cout << frames << " FPS" << std::endl;
        frames = 0;
        seconds += 1.0;
    }
}

int main(int argc, char* argv[]) {
    try
    {
        KineTypoGen app(argc, argv);
        return app.run();
    } catch(std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
