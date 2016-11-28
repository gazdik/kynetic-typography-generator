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

class Ease : public Action
{
public:
    Ease(Action *action, float p0, float p1, float p2, float p3);
    virtual ~Ease();

    virtual void update(float interval) override;
    virtual void init() override;
    virtual void setNode(Node *node) override;

private:
    Action *_action;
    float _p0, _p1, _p2, _p3;
};

class EaseIt : public Ease
{
public:
    EaseIt(Action *action) : Ease (action, 0.4f, 0.0f, 0.6f, 1.0f) {}
    virtual ~EaseIt() {}
};

class EaseOut : public Ease
{
public:
    EaseOut(Action *action) : Ease (action, 0.0f, 0.0f, 0.2f, 1.0f) {}
    virtual ~EaseOut() {}
};

class EaseIn : public Ease
{
public:
    EaseIn(Action *action) : Ease (action, 0.4f, 0.0f, 1.0f, 1.0f) {}
    virtual ~EaseIn() {}
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
    MoveBy(float duration, const glm::vec3 & vector);
    virtual ~MoveBy();

    virtual void update(float interval) override;
    virtual void init() override;

protected:
    glm::vec3 _startPosition;
    glm::vec3 _previousPosition;
    glm::vec3 _vector;
};

class MoveTo: public MoveBy
{
public:
    MoveTo(float duration, const glm::vec3 & endPosition);
    virtual ~MoveTo();

    virtual void init() override;

protected:
    glm::vec3 _endPosition;
};

class RotateBy: public Action
{
public:
    enum class Axis {
        X, Y, Z,
    };
public:
    RotateBy(float duration, float angle, Axis axis);
    RotateBy(float duration, float angleX, float angleY, float angleZ);
    virtual ~RotateBy();

    virtual void update(float interval) override;
    virtual void init() override;

protected:
    glm::vec3 _startRotation;
    glm::vec3 _previousRotation;
    glm::vec3 _angle;
};

class RotateTo : public RotateBy
{
public:
    RotateTo(float duration, float angle, Axis axis);
    RotateTo(float duration, float angleX, float angleY, float angleZ);
    virtual ~RotateTo();

    virtual void init() override;

private:
    glm::vec3 _endAngle;
};

class ScaleBy: public Action
{
public:
    ScaleBy(float duration, float scaleBy);
    ScaleBy(float duration, float scaleByX, float scaleByY, float scaleByZ);
    virtual ~ScaleBy();

    virtual void update(float interval) override;
    virtual void init() override;

protected:
    glm::vec3 _startScale;
    glm::vec3 _previousScale;
    glm::vec3 _scaleBy;
};

class ScaleTo: public ScaleBy
{
public:
    ScaleTo(float duration, float endScale);
    ScaleTo(float duration, float endScaleX, float endScaleY, float endScaleZ);
    virtual ~ScaleTo();

    virtual void init() override;

private:
    glm::vec3 _endScale;
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

class RemoveNode: public Action
{
public:
    RemoveNode();
    virtual ~RemoveNode();

    virtual void update(float interval) override;
    virtual void init() override;
};


#endif /* SRC_ACTION_H_ */
