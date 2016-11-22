/*
 * action.h
 *
 *  Created on: Nov 17, 2016
 *      Author: gazdik
 */

#ifndef SRC_ACTION_H_
#define SRC_ACTION_H_

#include "node.h"

#include <vector>
#include <deque>

class Action
{
public:
    Action(float duration);
    virtual ~Action() {};

    /**
     * Update state of the node.
     * @param interval A value between 0 (start of action) and 1 (end of action).
     */
    virtual void update(float interval) = 0;

    /**
     * Initialize action's specific data after adding node into action.
     */
    virtual void init() = 0;

    /**
     * Make step according to given delta time.
     * @param dt
     */
    virtual void step(float dt);

    /**
     * Test if the action has finished.
     * @return
     */
    virtual bool isRunning();

    /**
     * Set the node
     * @param node
     */
    virtual void setNode(Node *node);

    /**
     * Set duration of action
     * @param duration
     */
    void setDuration(float duration);

    /**
     * Get action's duration
     * @return Duration in seconds
     */
    float getDuration();

protected:
    Node *_node = nullptr;
    bool _running = true;
    float _duration;
    float _elapsedTime = 0.0f;
};

class Sequence : public Action
{
public:
    Sequence(Action *action1, ...);
    virtual ~Sequence();

    virtual void update(float interval) override;
    virtual void init() override;
    virtual void step(float dt) override;

private:
    void setNewAction();

    std::deque<Action *> _actions;
    Action *_currentAction;
};

class Spawn : public Action
{
public:
    Spawn(Action *action1, ...);
    virtual ~Spawn();

    virtual void update(float interval) override;
    virtual void init() override;
    virtual void step(float dt) override;
    virtual void setNode(Node *node) override;

private:
    std::vector<Action *> _actions;
};

class Delay : public Action
{
public:
    Delay(float duration);
    virtual ~Delay();

    virtual void update(float interval) override;
    virtual void init() override;
};


class MoveBy: public Action
{
public:
    MoveBy(float duration, const glm::vec2 & vector);
    virtual ~MoveBy();

    virtual void update(float interval) override;
    virtual void init() override;

protected:
    glm::vec2 _startPosition;
    glm::vec2 _previousPosition;
    glm::vec2 _vector;
};

class MoveTo: public MoveBy
{
public:
    MoveTo(float duration, const glm::vec2 & endPosition);
    virtual ~MoveTo();

    virtual void init() override;

protected:
    glm::vec2 _endPosition;
};

class RotateBy: public Action
{
public:
    RotateBy(float duration, float angle);
    virtual ~RotateBy();

    virtual void update(float interval) override;
    virtual void init() override;

protected:
    float _startRotation = 0;
    float _previousRotation = 0;
    float _angle;
};

class RotateTo : public RotateBy
{
public:
    RotateTo(float duration, float endAngle);
    virtual ~RotateTo();

    virtual void init() override;

private:
    float _endAngle;
};

class ScaleBy: public Action
{
public:
    ScaleBy(float duration, float scaleBy);
    ScaleBy(float duration, float scaleByX, float scaleByY);
    virtual ~ScaleBy();

    virtual void update(float interval) override;
    virtual void init() override;

protected:
    glm::vec2 _startScale;
    glm::vec2 _previousScale;
    glm::vec2 _scaleBy;
};

class ScaleTo: public ScaleBy
{
public:
    ScaleTo(float duration, float endScale);
    ScaleTo(float duration, float endScaleX, float endScaleY);
    virtual ~ScaleTo();

    virtual void init() override;

private:
    glm::vec2 _endScale;
};

/**
 * Modify the node alpha value from current value to 1.0.
 */
class FadeIn: public Action
{
public:
    FadeIn(float duration);
    virtual ~FadeIn();

    virtual void update(float interval) override;
    virtual void init() override;

private:
    float _startAlpha = 0.0f;
};

/**
 * Modify the node alpha value from current value to 0.0
 */
class FadeOut: public Action
{
public:
    FadeOut(float duration);
    virtual ~FadeOut();

    virtual void update(float interval) override;
    virtual void init() override;

private:
    float _startAlpha = 1.0f;
};


#endif /* SRC_ACTION_H_ */
