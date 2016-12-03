#ifndef WORDCLOUDEFFECT_H
#define WORDCLOUDEFFECT_H

#include "../effect.h"

class WordCloudEffect : public Effect
{
public:
    WordCloudEffect();
    virtual ~WordCloudEffect() {}
    float run(InputString& inputString, Node& inputNode, float startTime) override;
    int acceptsString(InputString const &inputString) override;
};

#endif // WORDCLOUDEFFECT_H
