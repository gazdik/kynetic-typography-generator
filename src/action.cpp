/*
 * action.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: gazdik
 */

#include "action.h"

#include <algorithm>
#include <cfloat>
#include <climits>

using namespace std;

Action::Action(float duration)
{
    setDuration(duration);
}

void Action::step(float dt)
{
    _elapsedTime += dt;

    if (_elapsedTime > _duration) {
        _elapsedTime = _duration;
        _running = false;
    }

    float interval = _elapsedTime / max(FLT_EPSILON, _duration);

    update(interval);
}

void Action::setNode(Node* node)
{
    _node = node;
    init();
}

bool Action::isRunning()
{
    return _running;
}

void Action::setDuration(float duration)
{
    _duration = duration <= 0 ? FLT_EPSILON : duration;
}

RotateBy::RotateBy(float duration, float angle) :
    Action (duration)
{
    _angle = angle;
}

RotateBy::~RotateBy()
{
}

void RotateBy::update(float interval)
{
    // Update start angle (another action can manipulate with the node)
    float currentRotation = _node->getRotation();
    float diff = currentRotation - _previousRotation;
    _startRotation += diff;

    float newRotation = _startRotation + (_angle * interval);
    _node->setRotation(newRotation);

    _previousRotation = newRotation;
}
void RotateBy::init()
{
    _startRotation = _previousRotation = _node->getRotation();
}

FadeIn::FadeIn(float duration) :
    Action(duration)
{
}

FadeIn::~FadeIn()
{
}

void FadeIn::update(float interval)
{
    float newAlpha = _startAlpha + ((1.0f - _startAlpha) * interval);

    if (newAlpha > 1.0f)
        newAlpha = 1.0f;

    _node->setAlpha(newAlpha);
}

void FadeIn::init()
{
    _startAlpha = _node->getAlpha();
}


FadeOut::FadeOut(float duration) :
    Action(duration)
{
}

FadeOut::~FadeOut()
{
}

void FadeOut::update(float interval)
{
    float newAlpha = _startAlpha - ((_startAlpha - 0.0f) * interval);

    if (newAlpha < 0.0f)
        newAlpha = 0.0f;

    _node->setAlpha(newAlpha);
}

void FadeOut::init()
{
    _startAlpha = _node->getAlpha();
}

MoveBy::MoveBy(float duration, const glm::vec2& vector) :
    Action(duration)
{
    setDuration(duration);
    _vector = vector;
}

MoveBy::~MoveBy()
{
}

void MoveBy::update(float interval)
{
    // Update start position (another action can manipulate with the node)
    glm::vec2 currentPosition = _node->getPosition();
    glm::vec2 diff = currentPosition - _previousPosition;
    _startPosition += diff;

    glm::vec2 newPosition = _startPosition + (_vector * interval);
    _node->setPosition(newPosition);

    _previousPosition = newPosition;
}

void MoveBy::init()
{
    _startPosition = _previousPosition = _node->getPosition();
}

MoveTo::MoveTo(float duration, const glm::vec2& endPosition) :
        MoveBy(duration, glm::vec2()), _endPosition { endPosition }
{
}

MoveTo::~MoveTo()
{
}

void MoveTo::init()
{
    _startPosition = _previousPosition = _node->getPosition();
    _vector = _endPosition - _startPosition;
}

RotateTo::RotateTo(float duration, float endAngle) :
        RotateBy(duration, 0.0f), _endAngle { endAngle }
{
}

RotateTo::~RotateTo()
{
}

void RotateTo::init()
{
    _startRotation = _previousRotation = _node->getRotation();
    _angle = _endAngle - _startRotation;
}

ScaleBy::ScaleBy(float duration, float scaleBy) :
        Action(duration), _scaleBy { scaleBy, scaleBy }
{
}

ScaleBy::ScaleBy(float duration, float scaleByX, float scaleByY) :
        Action(duration), _scaleBy { scaleByX, scaleByY }
{
}

ScaleBy::~ScaleBy()
{
}

void ScaleBy::update(float interval)
{
    // Update start scale (another action can manipulate with the node)
    glm::vec2 currentScale = _node->getScale();
    glm::vec2 diff = currentScale - _previousScale;
    _startScale += diff;

    glm::vec2 newScale = _startScale + (_scaleBy * interval);
    _node->setScale(newScale);

    _previousScale = newScale;
}


void ScaleBy::init()
{
    _startScale = _previousScale = _node->getScale();
}

ScaleTo::ScaleTo(float duration, float endScale) :
        ScaleBy(duration, 0.0f), _endScale { endScale, endScale }
{
}


ScaleTo::ScaleTo(float duration, float endScaleX, float endScaleY) :
        ScaleBy(duration, 0.0f), _endScale { endScaleX, endScaleY }
{
}

ScaleTo::~ScaleTo()
{
}

void ScaleTo::init()
{
    _startScale = _previousScale = _node->getScale();
    _scaleBy = _endScale - _startScale;
}
