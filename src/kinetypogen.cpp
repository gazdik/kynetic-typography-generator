#include "kinetypogen.h"

#include "constants.h"

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

    mainNode = new Group(WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);

    // Do the magic here

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int KineTypoGen::run()
{
    std::vector<Effect*> effects;

    // Debug effects
    //effects.push_back(new TestEffect());
//    effects.push_back(new CalibrationEffect());
//    effects.push_back(new SinkEffect());

    // Normal effects
    effects.push_back(new WordCloudEffect());
    effects.push_back(new RotateFlyEffect());
    effects.push_back(new LetterAside());
    effects.push_back(new OneWord());
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

    // TODO Calculate the exact value of Z position
    glm::vec3 cameraPos {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 960.0f};
    glm::vec3 cameraTarget {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f};
    glm::vec3 cameraDirection { 0.0f, 1.0f, 0.0f };

    // For orthogonal projection comment marked lines
    glm::mat4 projection;
//    projection = glm::ortho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1000.0f, 1000.0f);
    projection = glm::perspectiveFov(45.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.01f, 10000.0f); // !
    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraTarget, cameraDirection); // !

    mainNode->render(projection * view);
//    mainNode->render(projection);

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
