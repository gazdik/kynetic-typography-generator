#ifndef LETTERASIDE_H
#define LETTERASIDE_H

#include "../effect.h"

class LetterAside : public Effect
{
public:
    LetterAside();
    virtual ~LetterAside() {}
    float run(InputString& inputString, Node& inputNode, float startTime) override;
    bool acceptsString(InputString const &inputString) override;
};

#endif // LETTERASIDE_H
