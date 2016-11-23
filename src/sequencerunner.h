#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include <vector>
#include <string>
#include "effect.h"
#include <random>

class SequenceRunner
{
public:
    SequenceRunner(std::vector<Effect*> &effects);
    void run(std::string str, int seed, Triangle &mainNode);
private:
    std::vector<Effect*> _effects;
};

#endif // SEQUENCERUNNER_H
