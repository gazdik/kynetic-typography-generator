#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include "inputstring.h"
#include "node.h"

class Effect
{
public:
    virtual void run(std::string str, Node& inputNode);
    virtual bool isOK(InputString& inputString);
};

#endif // EFFECT_H
