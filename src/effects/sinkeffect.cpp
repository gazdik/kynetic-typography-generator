#include "sinkeffect.h"

SinkEffect::SinkEffect()
{

}

float SinkEffect::run(InputString &inputString, Node &inputNode, float startTime)
{
    inputString.read(1, SOT_WORD);
    return 0;
}

bool SinkEffect::acceptsString(const InputString &inputString)
{
    return true;
}
