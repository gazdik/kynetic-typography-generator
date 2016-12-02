#ifndef PILEUPEFFECT_H
#define PILEUPEFFECT_H

#include "../effect.h"

class PileUpEffect : public Effect
{
public:
    PileUpEffect();
    virtual ~PileUpEffect() {}
    float run(InputString& inputString, Node& inputNode, float startTime) override;
    bool acceptsString(InputString const &inputString) override;
    Text* newText(InputString &inputString, Node &inputNode, float width, Point &td);
    Text* newTextWithHeight(InputString &inputString, Node &inputNode, float height, Point &td);
    void transform(Text &t, float &time, Node &inputNode,
                   glm::vec3 startPos, glm::vec3 startRot,
                   glm::vec3 endPos, glm::vec3 endRot,
                   glm::vec3 scMoveBy, glm::vec3 scRotBy);
};

#endif // PILEUPEFFECT_H
