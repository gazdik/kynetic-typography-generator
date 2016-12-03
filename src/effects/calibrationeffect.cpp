/*
 * calibrationeffect.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: gazdik
 */

#include "effects/calibrationeffect.h"

#include "geometricshape.h"
#include "constants.h"
#include "macros.h"

CalibrationEffect::CalibrationEffect()
{
}

CalibrationEffect::~CalibrationEffect()
{
}

float CalibrationEffect::run(InputString& str, Node& inputNode, float startTime)
{
    UNUSED(str);
    inputNode.runAction(startTime,
        new MoveTo(1, glm::vec3(0, 0, 0))
    );

    auto fullscreen = new Square(WINDOW_WIDTH, WINDOW_HEIGHT);
    fullscreen->setColor(0.88, 0.43, 0.82);
    fullscreen->setAnchorPoint(0.0f, 0.0f, 0.0f);
    fullscreen->setPosition(0.0f, 0.0f, 0.0f);

    auto marker_bl = new Cube(30.0f, 30.0f, 30.0f);
    marker_bl->setAnchorPoint(0.0f, 0.0f, 0.5f);
    marker_bl->setPosition(0.0f, 0.0f);
    fullscreen->addChild(marker_bl);

    auto marker_br = new Cube(30.0f, 30.0f, 30.0f);
    marker_br->setAnchorPoint(1.0f, 0.0f, 0.5f);
    marker_br->setPosition(WINDOW_WIDTH, 0.0f);
    fullscreen->addChild(marker_br);

    auto marker_tl = new Cube(30.0f, 30.0f, 30.0f);
    marker_tl->setAnchorPoint(0.0f, 1.0f, 0.5f);
    marker_tl->setPosition(0.0, WINDOW_HEIGHT);
    fullscreen->addChild(marker_tl);

    auto marker_tr = new Cube(30.0f, 30.0f, 30.0f);
    marker_tr->setAnchorPoint(1.0f, 1.0f, 0.5f);
    marker_tr->setPosition(fullscreen->getContentSize());
    fullscreen->addChild(marker_tr);

    auto square = new Cube(200.0f, 200.0f, 200.0f);
    square->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 200.0f);
    square->runAction(startTime, new RotateBy(4.0f, 360.0f, RotateBy::Axis::Y));
    fullscreen->addChild(square);

    fullscreen->runAction(startTime + 3.0f, new Sequence(new FadeOut(1.0f),
            new RemoveNode(), nullptr));

    inputNode.addChild(fullscreen);

    return 4.0f;
}

int CalibrationEffect::acceptsString(const InputString& inputString)
{
    UNUSED(inputString);

    return 80;
}
