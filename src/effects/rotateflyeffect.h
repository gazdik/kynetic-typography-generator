#ifndef ROTATEFLYEFFECT_H
#define ROTATEFLYEFFECT_H

#include "../effect.h"

class RotateFlyEffect : public Effect
{
public:
    RotateFlyEffect();
    float run(InputString& inputString, Node& inputNode, float startTime) override;
    int acceptsString(InputString const &inputString) override;
};

#endif // ROTATEFLYEFFECT_H
