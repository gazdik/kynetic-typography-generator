#include "oneword.h"

OneWord::OneWord()
{

}

int OneWord::acceptsString(const InputString &inputString)
{
    return inputString.startsWith(1, SOT_WORD) ? 40 : 0;
}

float OneWord::run(InputString &inputString, Node &inputNode, float startTime)
{
    float owLeft = 640;
    float bottom = 500;

    inputNode.runAction(startTime,
        new MoveTo(0, glm::vec3(0, 0, 0))
    );

    // Subtle move of the whole scene to left
    inputNode.runAction(startTime,
        new MoveBy(3, glm::vec3(-40, 0, 0))
    );

    std::string w = inputString.read(1, SOT_WORD);

    float sumWidth = 0;

    for (int i = 0; i < w.size(); ++i) {
        auto sw = new Text(w.substr(i, 1), "Roboto-Thin");
        sw->setScale(1.41);
        sw->setAlpha(0);
        sw->setPosition(owLeft + sumWidth, bottom);
        sumWidth += sw->getDimensions().x + 50;

        // Fade in on start
        sw->runAction(startTime + i * 0.1f,
                      new FadeIn(0.3));
        // Subtle zoom-in of each letter during the whole animation

        sw->runAction(startTime + i * 0.2f,
                      //new EaseIn(new MoveBy(4, glm::vec3(0, 0, 20))));
                      new EaseOut(new ScaleBy(4, .2f)));
        sw->runAction(startTime + 0.3f + i * 0.3f,
                      new FadeOut(1));
        inputNode.addChild(sw);
    }


    float dur = 0.3f * (w.size()+1);

    inputNode.runAction(startTime + dur,
        new MoveTo(0, glm::vec3(0, -1080, 0))
    );

    inputNode.runAction(startTime + dur - 0.3f,
        new FadeOut(0.3)
    );

    return dur;
}
