#include "kinetypogen.h"

const char KineTypoGen::fontFile[] = "fonts/DejaVuSerif-Bold.ttf";

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

    mainNode = new Group();

    // Do the magic here

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

KineTypoGen::~KineTypoGen() {
    delete(glView);
}
