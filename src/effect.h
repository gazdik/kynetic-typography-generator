#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include "inputstring.h"
#include "node.h"
#include "action.h"
#include "text.h"
#include "group.h"

class Effect
{
public:
    virtual ~Effect() {}
    virtual float run(InputString& inputString, Node& inputNode, float startTime) = 0;
    virtual bool acceptsString(InputString const &inputString) = 0;
};

#endif // EFFECT_H
