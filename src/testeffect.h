#ifndef TESTEFFECT_H
#define TESTEFFECT_H

#include "effect.h"
#include "triangle.h"
#include "action.h"

class TestEffect : public Effect
{
public:
    void run(std::string str, Triangle &inputNode);
    bool acceptsString(InputString &inputString);
private:
    Triangle *triangle1, *triangle2;
};

#endif // TESTEFFECT_H
