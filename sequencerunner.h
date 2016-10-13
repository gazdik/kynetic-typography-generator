#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include <vector>
#include <string>

class SequenceRunner
{
public:
    SequenceRunner(std::vector<std::string> effects);
    void run(std::string str, int seed);
};

#endif // SEQUENCERUNNER_H
