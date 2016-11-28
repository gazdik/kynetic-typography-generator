#include "testeffect.h"

#include "geometricshape.h"


float TestEffect::run(InputString &str, Node &inputNode, float startTime)
{
    inputNode.runAction(startTime,
        new MoveTo(1, glm::vec3(0, 0, 0))
    );

    triangle1 = new Triangle();
    triangle1->setContentSize(100.0f, 100.0f);
    triangle1->setPosition(500.0f, 500.0f);
    triangle1->setZRotation(-45.0f);
    triangle1->setColor(0.99, 0.26, 0.6);

    triangle2 = new Triangle();
    triangle2->setContentSize(50.0f, 50.0f);
    triangle2->setPosition(50.0f, 125.0f);
    triangle2->setColor(0.99, 0.7, 0.1);
    triangle2->runAction(startTime, new RotateTo(2.0f, 360.0f, 360.0f, 360.0f));
    triangle2->runAction(startTime, new ScaleTo(2.0f, 3.0f));

    triangle1->addChild(triangle2);
    triangle1->setAlpha(1.0f);
    triangle1->runAction(startTime, new EaseIt(
            new MoveTo(2.0f, glm::vec3(1920.0f / 2.0f, 850.0f, 0.0f))
    ));
    triangle1->runAction(startTime, new RotateTo(2.0f, 360.0f, 360.0f, 360.0f));

    auto text = new Text(str.read(1, SOT_WORD), "DejaVuSerif-Bold");
    text->setPosition(20, 300);
    text->runAction(startTime,
        new EaseOut(
            new MoveBy(4, glm::vec3(300, 0, 0))
        )
    );
    text->runAction(startTime, new EaseOut(
        new ScaleBy(2, 0.5f))
    );
    text->runAction(startTime + 1.8f,
        new EaseOut(
            new FadeOut(1.0f)
        )
    );

    inputNode.addChild(triangle1);
    inputNode.addChild(text);

    /*
     * Eeasing curves
     */
    auto triangle3 = new Triangle();
    triangle3->setZRotation(90.0f);
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

    auto easeLikeGoogle = new EaseIt(new MoveBy(2.0f, glm::vec3(1800.0f, 0.0f, 0.0f)));
    auto easeIn = new EaseIn(new MoveBy(2.0f, glm::vec3(1800.0f, 0.0f, 0.0f)));
    auto easeOut = new EaseOut(new MoveBy(2.0f, glm::vec3(1800.0f, 0.0f, 0.0f)));
    triangle3->runAction(startTime + 2, easeLikeGoogle);
    triangle4->runAction(startTime + 2, easeIn);
    triangle5->runAction(startTime + 2, easeOut);

    /*
     * Testing the anchor point and content size
     */
    auto cube1 = new Cube();
    cube1->setContentSize(130.0, 130.0f, 130.0f);
    cube1->setPosition(1920.0f / 2.0f, 1080.0f / 2.0f);
    cube1->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
    cube1->setAnchorPoint(0.5f, 0.5f, 0.5f);
    cube1->runAction(startTime, new RotateBy(4.0f, 720.0f, RotateBy::Axis::X));
    cube1->runAction(startTime, new RotateBy(4.0f, 720.0f, RotateBy::Axis::Y));
    cube1->runAction(startTime, new RotateBy(4.0f, 720.0f, RotateBy::Axis::Z));
    cube1->runAction(startTime, new ScaleTo(4.0f, 0.2f));
    inputNode.addChild(cube1);

    auto cube2 = new Cube(*cube1);
    cube2->setColor(0.3, 0.7, 0.1);
    // Now you can position the cube by it's origin point (bottom front left corner)
    cube2->ignoreAnchorPointForPositioning(true);
    // Place the cube on the top right corner of the first cube.
    cube2->setPosition(cube2->getContentSize());
    cube1->addChild(cube2);

    /*
     *  Square...
     */
    auto square = new Square();
    square->setContentSize(200.0f, 200.0f);
    square->setColor(0.88, 0.43, 0.82);
    square->setPosition(1500.0f, 600.0f);
    square->runAction(startTime, new RotateBy(4.0f, 360.0f, RotateBy::Axis::Z));
    inputNode.addChild(square);

    /*
     * Rotate the whole scene
     */
//    inputNode.setAnchorPoint(0.0f, 0.5f, 0.0);
//    inputNode.runAction(startTime + 4.0f,
//        new EaseOut(new RotateBy(4.0f, 180.0f, RotateBy::Axis::Y))
//    );

    inputNode.runAction(startTime + 4,
        new MoveTo(1, glm::vec3(0, -1080, 0))
    );

    auto tempNode = new Cube(100, 130, 200);
    tempNode->setPosition(800, 200, 0.0);
    tempNode->runAction(startTime,
            new Sequence(
                    new RotateBy(2.0f, 350.0f, RotateBy::Axis::X),
                    new RemoveNode(),
                    nullptr)
    );
    inputNode.addChild(tempNode);

    return 4;
}

bool TestEffect::acceptsString(InputString const &inputString)
{
    UNUSED(inputString);
    return true;
}
