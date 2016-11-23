#include "sequencerunner.h"

// debug
#include <iostream>

SequenceRunner::SequenceRunner(std::vector<Effect*> &effects)
{
    _effects = effects;
    // TODO: Implement method body
}

void SequenceRunner::run(std::string str, int seed, Triangle &mainNode)
{
    // TODO: Implement text reading loop
    srand(seed);

    int effectIndex = rand() % _effects.size();
    _effects[effectIndex]->run(str, mainNode);
}
