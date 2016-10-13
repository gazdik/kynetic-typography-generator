#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include "inputstring.h"
#include "node.h"

class Effect
{
public:
    virtual void run(std::string str, Node& inputNode) = 0;
    virtual bool acceptsString(InputString& inputString) = 0;
};

#endif // EFFECT_H
