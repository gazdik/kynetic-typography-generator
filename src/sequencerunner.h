#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include <vector>
#include <string>
#include <random>
#include <stdexcept>

#include "effect.h"
#include "group.h"
#include "inputstring.h"
#include "action.h"


class SequenceRunner
{
public:
    SequenceRunner(std::vector<Effect*> &effects);
    void run(std::string str, int seed, Node &mainNode);
private:
    void planRandomEffect(float time, InputString &inputString, Node &mainNode);
    std::vector<Effect*> _effects;
};

#endif // SEQUENCERUNNER_H
