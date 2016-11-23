#include "testeffect.h"


void TestEffect::run(std::string str, Triangle &inputNode)
{
    triangle1 = new Triangle();
    triangle1->setContentSize(100.0f, 100.0f);
    triangle1->setPosition(100, 100);
    triangle1->setRotation(-45.0f);
    triangle1->setColor(0.99, 0.26, 0.6);

    triangle2 = new Triangle();
    triangle2->setContentSize(50.0f, 50.0f);
    triangle2->setPosition(0.0f, 75.0f);
    triangle2->setColor(0.99, 0.7, 0.1);
    triangle2->setAlpha(0.0f);
    triangle2->runAction(new FadeIn(2.0f));
    triangle2->runAction(new RotateTo(2.0f, 360.0f));
    triangle2->runAction(new ScaleTo(2.0f, 3.0f, 3.0f));

    triangle1->addChild(triangle2);
    triangle1->setAlpha(1.0f);
    triangle1->runAction(new FadeOut(2.0f));
    triangle1->runAction(new MoveTo(2.0f, glm::vec2(400.0f, 400.0f)));
    triangle1->runAction(new RotateTo(2.0f, 360.0f));

    inputNode.addChild(triangle1);
}

bool TestEffect::acceptsString(InputString &inputString)
{
    return true;
}
