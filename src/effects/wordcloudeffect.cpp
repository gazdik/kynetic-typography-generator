#include "wordcloudeffect.h"

WordCloudEffect::WordCloudEffect()
{
}

const int WORDS_COUNT = 20;
const float PI = 3.141593f;

bool WordCloudEffect::acceptsString(const InputString &inputString)
{
    return inputString.startsWith(WORDS_COUNT, SOT_WORD);
}

float WordCloudEffect::run(InputString &inputString, Node &inputNode, float startTime)
{
    int sphereCount = 3;
    float smallestRadius = 2000;
    float radiusMultiplier = 2;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(960, 500, -smallestRadius))
    );

    // Place words in sphereCount spheres

    float radius = smallestRadius;
    float time = startTime;
    for (int s = 0; s < sphereCount; ++s) {

        int sphereWordCount = glm::floor(WORDS_COUNT / glm::pow(2, s));

        float angle = 0;
        float angleDelta = 360 / sphereWordCount;
        int ySign = 1;
        for (int w = 0; w < sphereWordCount; ++w) {

            auto t = new Text(inputString.read(1, SOT_WORD));
            t->setLineLength(100000);
            t->setScale(2.1);
            Point tDim = t->getDimensions();
            // Center text in its group
            t->setPosition(-tDim.x / 2, -tDim.y / 2);

            auto tg = new Group();
            tg->addChild(t);
            tg->setPosition(
                radius * glm::sin(angle * PI / 180),
                ySign * 300,
                radius * glm::cos(angle * PI / 180.0f)
            );
            tg->setRotation(glm::vec3(0, -angle, 0));

            inputNode.addChild(tg);

//            inputNode.runAction(
//                time,
//                new Ease(new RotateTo(0.5f, 0, angle - angleDelta/2, 0),
//                                  .3f, 0, .43f, -3.66f)
//            );

//            inputNode.runAction(
//                time + 0.5f,
//                new Ease(new RotateTo(0.5f, 0, angle, 0),
//                              .57f, 3.66f, .7f, 1)
//            );


            inputNode.runAction(
                time,
                new EaseOut(new RotateTo(0.5f, 0, angle, 0))
            );

            time += 0.7f;
            ySign *= -1;
            angle += angleDelta;


        }

        inputNode.runAction(
            time,
            new EaseOut(new MoveBy(0.5f, glm::vec3(0, 0, -smallestRadius)))
        );

        radius += smallestRadius;
    }

    // Implementation

    float dur = time;

    inputNode.runAction(startTime + dur,
        new MoveTo(0, glm::vec3(- 10*sphereCount * smallestRadius, 0, 0))
    );

    return dur;
}
