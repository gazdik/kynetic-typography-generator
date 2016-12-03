#ifndef TESTEFFECT_H
#define TESTEFFECT_H

#include "effect.h"
#include "geometricshape.h"
#include "text.h"
#include "action.h"
#include "macros.h"

class TestEffect : public Effect
{
public:
    ~TestEffect() {}
    float run(InputString &str, Node &inputNode, float startTime) override;
    int acceptsString(InputString const &inputString) override;

    void bar();
    void foobar(const char *msg);
private:
    Triangle *triangle1, *triangle2;
};

#endif // TESTEFFECT_H
