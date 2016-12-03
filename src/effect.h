#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <ctype.h>
#include <math.h>
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

    /**
     * @brief acceptsString
     * @param inputString
     * @return integer in interval 0-100 where 0 means cannot handle, 1-100 says
     *         how appropriate the effect is for string: 100 = very excited
     */
    virtual int acceptsString(InputString const &inputString) = 0;
    static std::string toUpper(std::string str);
};

#endif // EFFECT_H
