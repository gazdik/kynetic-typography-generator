#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include <vector>
#include <string>
#include "effect.h"

class SequenceRunner
{
public:
    SequenceRunner(std::vector<Effect> effects);
    void run(std::string str, int seed);
};

#endif // SEQUENCERUNNER_H
