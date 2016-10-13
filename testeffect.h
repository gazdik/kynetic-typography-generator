#ifndef TESTEFFECT_H
#define TESTEFFECT_H

#include "effect.h"

class TestEffect : public Effect
{
public:
    void run(std::string str, Node &inputNode);
    bool acceptsString(InputString &inputString);
};

#endif // TESTEFFECT_H
