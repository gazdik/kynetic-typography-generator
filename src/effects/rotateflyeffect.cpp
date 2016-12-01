#include "rotateflyeffect.h"

RotateFlyEffect::RotateFlyEffect()
{

}

static const int LINES_COUNT = 4;

bool RotateFlyEffect::acceptsString(const InputString &inputString)
{
    return inputString.startsWith(LINES_COUNT, SOT_WORD, SOM_MEDIUM | SOM_LONG);
}

float RotateFlyEffect::run(InputString &inputString, Node &inputNode, float startTime)
{
    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(0, 0, 0))
    );

    float sumHeight = 0;
    auto textGroup = new Group();
    for (int i = 0; i < LINES_COUNT; ++i)
    {
        auto ow = new Text(inputString.read(1, SOT_WORD));
        ow->setLineLength(100000);
        ow->setScaleForWidth(350);

        ow->setRotation(glm::vec3(0, 160, 0));
        float height = ow->getDimensions().y;
        float yPos = 1080 - height - sumHeight;
        ow->setPosition(200, yPos - 500, 600);

        // Arrival
        ow->runAction(startTime + i*0.05, new EaseOut(new RotateTo(0.6, 0, 0, 0)));
        ow->runAction(startTime + i*0.05, new EaseOut(new MoveTo(0.6, glm::vec3(800, yPos, 0))));

        // Leave
        ow->runAction(startTime + 2 + i*0.05, new EaseIt(new RotateTo(0.3, 0, -100, 0)));
        ow->runAction(startTime + 2 + i*0.05, new EaseIt(new FadeOut(0.3)));
        //ow->runAction(startTime + 2 + i*0.05, new EaseIn(new ScaleTo(0.6, 0)));


        sumHeight += ow->getDimensions().y + 20;


        textGroup->addChild(ow);
    }

    textGroup->setPosition(0, -(1080 - sumHeight)/2, 0);

    inputNode.addChild(textGroup);

    inputNode.runAction(startTime + 4,
        new MoveTo(0, glm::vec3(-1920, 0, 0))
    );

    return startTime + 2 + LINES_COUNT*0.05 + 0.3;
}
