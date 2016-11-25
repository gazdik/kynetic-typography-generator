#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include "inputstring.h"
#include "node.h"
#include "triangle.h"

class Effect
{
public:
    virtual ~Effect() {}
    virtual void run(std::string str, Triangle& inputNode) = 0;
    virtual bool acceptsString(InputString& inputString) = 0;
};

#endif // EFFECT_H
