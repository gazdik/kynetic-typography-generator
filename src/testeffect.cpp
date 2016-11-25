#include "testeffect.h"


void TestEffect::run(std::string str, Triangle &inputNode)
{
    triangle1 = new Triangle();
    triangle1->setContentSize(100.0f, 100.0f);
    triangle1->setPosition(350.0f, 350.0f);
    triangle1->setZRotation(-45.0f);
    triangle1->setColor(0.99, 0.26, 0.6);

    triangle2 = new Triangle();
    triangle2->setContentSize(50.0f, 50.0f);
    triangle2->setPosition(0.0f, 75.0f);
    triangle2->setColor(0.99, 0.7, 0.1);
    triangle2->setAlpha(0.0f);
    triangle2->runAction(new FadeIn(2.0f));
    triangle2->runAction(new RotateTo(2.0f, 360.0f, 360.0f, 360.0f));
    triangle2->runAction(new ScaleTo(2.0f, 3.0f));

    triangle1->addChild(triangle2);
    triangle1->setAlpha(1.0f);
    triangle1->runAction(new FadeOut(2.0f));
    triangle1->runAction(new MoveTo(2.0f, glm::vec3(400.0f, 400.0f, 0.0f)));
    triangle1->runAction(new RotateTo(2.0f, 360.0f, 360.0f, 360.0f));

    auto text = new Text(str);
    text->setPosition(20, 75);
    text->runAction(new EaseOut(
        new MoveBy(4, glm::vec3(300, 0, 0))
    ));
    text->runAction(new EaseOut(
        new ScaleBy(2, 0.5f)
    ));
    text->runAction(new Sequence(
        new Delay(1.8f),
        new EaseOut(
            new FadeOut(1.0f)
        ),
        nullptr
    ));

    inputNode.addChild(triangle1);
    inputNode.addChild(text);

    /*
     * Eeasing curves
     */
    auto triangle3 = new Triangle();
    triangle3->setZRotation(-90.0f);
    triangle3->setColor(0.13f, 0.59f, 0.95f);
    triangle3->setContentSize(75.0f, 75.0f);
    triangle3->setPosition(50.0f, 50.0f);
    inputNode.addChild(triangle3);

    auto triangle4 = new Triangle(*triangle3);
    triangle4->setPosition(50.0f, 150.0f);
    triangle4->setColor(0.85f, 0.26f, 0.21f);
    inputNode.addChild(triangle4);

    auto triangle5 = new Triangle(*triangle3);
    triangle5->setPosition(50.0f, 250.0f);
    triangle5->setColor(0.30f, 0.68f, 0.31f);
    inputNode.addChild(triangle5);

    auto easeLikeGoogle = new Sequence(new Delay(2.0f),
            new EaseIt(new MoveBy(2.0f, glm::vec3(700.0f, 0.0f, 0.0f))), nullptr);
    auto easeIn = new Sequence(new Delay(2.0f),
            new EaseIn(new MoveBy(2.0f, glm::vec3(700.0f, 0.0f, 0.0f))), nullptr);
    auto easeOut = new Sequence(new Delay(2.0f),
            new EaseOut(new MoveBy(2.0f, glm::vec3(700.0f, 0.0f, 0.0f))), nullptr);
    triangle3->runAction(easeLikeGoogle);
    triangle4->runAction(easeIn);
    triangle5->runAction(easeOut);

}

bool TestEffect::acceptsString(InputString &inputString)
{
    UNUSED(inputString);
    return true;
}
