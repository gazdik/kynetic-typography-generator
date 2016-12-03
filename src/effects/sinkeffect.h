#ifndef SINKEFFECT_H
#define SINKEFFECT_H

#include "../effect.h"

class SinkEffect : public Effect
{
public:
    SinkEffect();
    float run(InputString& inputString, Node& inputNode, float startTime) override;
    int acceptsString(InputString const &inputString) override;
};

#endif // SINKEFFECT_H
