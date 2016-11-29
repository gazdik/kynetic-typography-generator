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
    float owLeft = 640;
    int owLines = 3;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(0, 0, 0))
    );

    // Subtle zoom-in
    inputNode.setAnchorPoint(960, 525, 0);
    inputNode.runAction(startTime,
                  new EaseIt(new ScaleBy(4, .06f)));

    auto sw = new Text(inputString.read(1, SOT_WORD));
    sw->setAlpha(0);
    sw->setAlignment(ALIGN_RIGHT);
    sw->setLineLength(owLeft - 50);
    sw->setScale(2.8f);

    Point swD = sw->getDimensions();
    float bottom = (1080 - swD.y) / 2.0f;
    sw->setPosition(0, bottom);

    inputNode.addChild(sw);
    sw->runAction(startTime, new FadeIn(0.3f));

    float owLineHeight = swD.y / owLines;
    float fadeoutTime = 0.8f;

    for (int i = 0; i < owLines; ++i) {
        auto ow = new Text(inputString.read(1, SOT_WORD));
        ow->setPosition(owLeft, bottom + (owLines - 1) * owLineHeight - i * owLineHeight);
        ow->setScale(1.55f);

        ow->setAlpha(0);
        inputNode.addChild(ow);
        ow->runAction(startTime + 0.1f + i * 0.1f, new FadeIn(0.3f));
        ow->runAction(startTime + 0.5 + owLines * .1f, new EaseOut(new FadeOut(0.7f)));
    }


    sw->runAction(startTime + 0.5 + owLines * .1f, new FadeOut(1));

    float dur = 1 + owLines * 0.1f + 0.2 + fadeoutTime;

    inputNode.runAction(startTime + dur,
        new MoveTo(0, glm::vec3(-1920, 0, 0))
    );

    return dur;
}
