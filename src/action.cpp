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

using namespace std;

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

