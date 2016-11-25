#ifndef TESTEFFECT_H
#define TESTEFFECT_H

#include "effect.h"
#include "triangle.h"
#include "text.h"
#include "action.h"
#include "macros.h"

class TestEffect : public Effect
{
public:
    ~TestEffect() {}
    void run(std::string str, Node &inputNode) override;
    bool acceptsString(InputString &inputString) override;
private:
    Triangle *triangle1, *triangle2;
};

#endif // TESTEFFECT_H
