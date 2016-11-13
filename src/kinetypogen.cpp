#include "kinetypogen.h"

KineTypoGen::KineTypoGen(int& argc, char* argv[])
{
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

int KineTypoGen::run()
{
    // TODO: vector with abstract class type
    std::vector<Effect*> effects;
    effects.push_back(new TestEffect());
    // Effects declarations go here

    SequenceRunner sequenceRunner(effects);
    sequenceRunner.run(str, 42);

    for (Effect* effect : effects) {
        delete(effect);
    }
    return 0;
}

int new_main(int argc, char* argv[]) {
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
