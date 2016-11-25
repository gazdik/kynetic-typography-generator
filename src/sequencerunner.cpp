#include "sequencerunner.h"

// debug
#include <iostream>

SequenceRunner::SequenceRunner(std::vector<Effect*> &effects)
{
    if (effects.size() == 0) {
        throw std::runtime_error("Cannot create SequenceRunner with no effects");
    }
    _effects = effects;
}

void SequenceRunner::run(std::string str, int seed, Triangle &mainNode)
{
    // TODO: Implement text reading loop
    srand(seed);

    int effectIndex = rand() % _effects.size();
    _effects[effectIndex]->run(str, mainNode);
}
