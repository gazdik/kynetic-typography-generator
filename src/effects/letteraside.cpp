#include "letteraside.h"

LetterAside::LetterAside()
{

}

bool LetterAside::acceptsString(const InputString &inputString)
{
    return (
        inputString.startsWith(1, SOT_WORD, SOM_SHORT) &&
        inputString.startsWith(3, SOT_WORD)
    );
}

float LetterAside::run(InputString &inputString, Node &inputNode, float startTime)
{
    float owScale = 2;
    float owLineHeight = 160;
    float owLeft = 640;
    float bottom = 450;
    int owLines = 3;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(0, 0, 0))
    );

    auto sw = new Text(inputString.read(1, SOT_WORD));
    sw->setPosition(owLeft - 320, bottom);
    sw->setScale(4);
    inputNode.addChild(sw);

    for (int i = 0; i < owLines; ++i) {
        auto ow = new Text(inputString.read(1, SOT_WORD));
        ow->setPosition(owLeft, bottom + owLines * owLineHeight - i * owLineHeight);
        ow->setScale(owScale);
        inputNode.addChild(ow);
    }

    inputNode.runAction(startTime + 3,
        new MoveTo(0, glm::vec3(-1920, 0, 0))
    );

    return 3;
}
