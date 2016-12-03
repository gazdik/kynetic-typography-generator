#ifndef ONEWORD_H
#define ONEWORD_H

#include "../effect.h"

class OneWord : public Effect
{
public:
    OneWord();
    virtual ~OneWord() {}
    float run(InputString& inputString, Node& inputNode, float startTime) override;
    int acceptsString(InputString const &inputString) override;
};

#endif // ONEWORD_H
