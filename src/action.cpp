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
#include <cstdarg>
#include <cmath>

using namespace std;

float bezierFunction( float t, float p0, float p1, float p2, float p3 )
{
    return (powf(1-t,3) * p0
            + 3 * powf(1-t,2) * t * p1
            + 3 * (1-t) * powf(t,2) * p2
            + powf(t,3) * p3 );
}

/* MIT License
 *
 * cubic_bezier - use bezier curve for transition easing function
 * Copyright (c) 2012 Gaetan Renaudeau <renaudeau.gaetan@gmail.com>
 */

float A(float aA1, float aA2) { return 1.0f - 3.0f * aA2 + 3.0f * aA1; }
float B(float aA1, float aA2) { return 3.0f * aA2 - 6.0f * aA1; }
float C(float aA1) { return 3.0f * aA1; }

/**
 * Returns x(t) given t, x1 and x2, or y(t) given t, y1 and y2
 */
float calcBezier(float aT, float aA1, float aA2)
{
    return ((A(aA1, aA2) * aT + B(aA1, aA2)) * aT + C(aA1)) * aT;
}

float getSlope(float aT, float aA1, float aA2)
{
    return 3.0f * A(aA1, aA2) * aT * aT + 2.0f * B(aA1, aA2) * aT + C(aA1);
}

float cubic_bezier(float t, float mX1, float mY1, float mX2, float mY2)
{
    if (mX1 == mY1 && mX2 == mY2) return t;    // linear

    float aGuessT = t;
    for (int i = 0; i < 4; i++) {
        float currentSlope = getSlope(aGuessT, mX1, mX2);
        if (currentSlope == 0.0f) return aGuessT;
        float currentX = calcBezier(aGuessT, mX1, mX2) - t;
        aGuessT -= currentX / currentSlope;
    }

    return calcBezier(aGuessT, mY1, mY2);
}

Action::Action(float duration)
{
    setDuration(duration);
}

void Action::step(float dt)
{
    _elapsedTime += dt;

    float interval = _elapsedTime / max(FLT_EPSILON, _duration);

    if (interval > 1.0f) {
        interval = 1.0f;
        _elapsedTime = _duration;
        _running = false;
    }

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

float Action::getDuration()
{
    return _duration;
}


RotateBy::RotateBy(float duration, float angle, Axis axis) :
    Action (duration), _angle { 0.0, 0.0, 0.0 }
{
    switch (axis) {
        case Axis::X:
            _angle.x = angle;
            break;
        case Axis::Y:
            _angle.y = angle;
            break;
        case Axis::Z:
            _angle.z = angle;
            break;
        default:
            break;
    }
}

RotateBy::RotateBy(float duration, float angleX, float angleY, float angleZ) :
        Action(duration)
{
    _angle.x = angleX;
    _angle.y = angleY;
    _angle.z = angleZ;
}

RotateBy::~RotateBy()
{
}

void RotateBy::update(float interval)
{
    // Update start angle (another action can manipulate with the node)
    glm::vec3 currentRotation = _node->getRotation();
    glm::vec3 diff = currentRotation - _previousRotation;
    _startRotation += diff;

    glm::vec3 newRotation = _startRotation + (_angle * interval);
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

MoveBy::MoveBy(float duration, const glm::vec3& vector) :
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
    glm::vec3 currentPosition = _node->getPosition();
    glm::vec3 diff = currentPosition - _previousPosition;
    _startPosition += diff;

    glm::vec3 newPosition = _startPosition + (_vector * interval);
    _node->setPosition(newPosition);

    _previousPosition = newPosition;
}

void MoveBy::init()
{
    _startPosition = _previousPosition = _node->getPosition();
}

MoveTo::MoveTo(float duration, const glm::vec3& endPosition) :
        MoveBy(duration, glm::vec3()), _endPosition { endPosition }
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

RotateTo::RotateTo(float duration, float angle, Axis axis) :
        RotateBy(duration, 0.0f, axis), _endAngle { 0.0f, 0.0f, 0.0f }
{
    switch (axis) {
        case Axis::X:
            _endAngle.x = angle;
            break;
        case Axis::Y:
            _endAngle.y = angle;
            break;
        case Axis::Z:
            _endAngle.z = angle;
            break;
        default:
            break;
    }
}

RotateTo::RotateTo(float duration, float angleX, float angleY, float angleZ) :
        RotateBy(duration, 0.0f, 0.0f, 0.0f), _endAngle { angleX, angleY, angleZ }
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
        Action(duration), _scaleBy { scaleBy, scaleBy, scaleBy }
{
}

ScaleBy::ScaleBy(float duration, float scaleByX, float scaleByY, float scaleByZ) :
        Action(duration), _scaleBy { scaleByX, scaleByY, scaleByZ }
{
}

ScaleBy::~ScaleBy()
{
}

void ScaleBy::update(float interval)
{
    // Update start scale (another action can manipulate with the node)
    glm::vec3 currentScale = _node->getScale();
    glm::vec3 diff = currentScale - _previousScale;
    _startScale += diff;

    glm::vec3 newScale = _startScale + (_scaleBy * interval);
    _node->setScale(newScale);

    _previousScale = newScale;
}


void ScaleBy::init()
{
    _startScale = _previousScale = _node->getScale();
}

ScaleTo::ScaleTo(float duration, float endScale) :
        ScaleBy(duration, 0.0f), _endScale { endScale, endScale, endScale }
{
}


ScaleTo::ScaleTo(float duration, float endScaleX, float endScaleY, float endScaleZ) :
        ScaleBy(duration, 0.0f), _endScale { endScaleX, endScaleY, endScaleZ }
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

Sequence::Sequence(Action* action1, ...) :
        Action (0.0f)
{
    _actions.push_back(action1);

    va_list actions;

    va_start(actions, action1);
    while(action1)
    {
        action1 = va_arg(actions, Action *);
        if (action1 != nullptr)
            _actions.push_back(action1);
    }
    va_end(actions);

    for (auto action: _actions) {
        _duration += action->getDuration();
    }

    _currentAction = _actions.front();
}

Sequence::~Sequence()
{
    for (auto action: _actions)
        delete action;
}

void Sequence::update(float interval)
{
}

void Sequence::init()
{
    _currentAction->setNode(_node);
}

void Sequence::step(float dt)
{
    if (!_currentAction->isRunning()) {
        setNewAction();

        if (_actions.empty()) {
            _running = false;
            return;
        }
    }

    // Useless. Maybe for future use.
    _elapsedTime += dt;

    _currentAction->step(dt);
}

void Sequence::setNewAction()
{
    // Delete old action
    delete _currentAction;
    _actions.pop_front();

    // Set new one
    if (! _actions.empty()) {
        _currentAction = _actions.front();
        _currentAction->setNode(_node);
    }
}

Spawn::Spawn(Action* action1, ...) :
        Action(0.0f)
{
    _actions.push_back(action1);

    va_list actions;

    va_start(actions, action1);
    while(action1)
    {
        action1 = va_arg(actions, Action *);
        if (action1 != nullptr)
            _actions.push_back(action1);
    }
    va_end(actions);

    for (auto action: _actions)
        _duration = max(_duration, action->getDuration());
}

Spawn::~Spawn()
{
}

void Spawn::update(float interval)
{
}

void Spawn::init()
{
    for (auto action: _actions)
        action->setNode(_node);
}

void Spawn::step(float dt)
{
    for (auto it = _actions.begin(); it != _actions.end(); /* nothing */) {
        auto action = *it;

        action->step(dt);

        if (action->isRunning()) {
            it++;
        }
        else {
            delete *it;
            it = _actions.erase(it);
        }
    }

    if (_actions.empty())
        _running = false;
}

void Spawn::setNode(Node* node)
{
    _node = node;
    for (auto action: _actions)
        action->setNode(node);
}

Delay::Delay(float duration) :
        Action(duration)
{
}

Delay::~Delay()
{
}

void Delay::update(float interval)
{
}

void Delay::init()
{
}

Ease::Ease(Action* action, float p0, float p1, float p2, float p3) :
        Action(action->getDuration()), _action { action }, _p0 { p0 },
        _p1 { p0 }, _p2 { p2 }, _p3 { p3 }
{

}

Ease::~Ease()
{
    delete _action;
}

void Ease::update(float interval)
{
    interval = cubic_bezier(interval, _p0, _p1, _p2, _p3);
    _action->update(interval);
    _running = _action->isRunning();
}

void Ease::init()
{
    _action->setNode(_node);
}


void Ease::setNode(Node* node)
{
    _node = node;
    _action->setNode(node);
}
