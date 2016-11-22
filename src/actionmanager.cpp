/*
 * actionmanager.cpp
 *
 *  Created on: Nov 21, 2016
 *      Author: gazdik
 */

#include "actionmanager.h"

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

ActionManager* ActionManager::getInstance()
{
    static ActionManager instance;
    return &instance;
}

void ActionManager::addAction(Action* action, Node* node)
{
    action->setNode(node);
    _actions.insert(action);
}

void ActionManager::removeAction(Action* action)
{
    if (_actions.count(action) > 0)
        _actions.erase(action);
}

void ActionManager::update(float time)
{
    if (_firstUpdate) {
        _firstUpdate = false;
        _previousTime = time;
        return;
    }

    float dt = time - _previousTime;
    _previousTime = time;

    for (auto it = _actions.begin(); it != _actions.end(); /* nothing */) {
        auto action = *it;

        action->step(dt);

        if (action->isRunning())
            it++;
        else
            removeAction(it);
    }
}

void ActionManager::removeAction(
        std::set<Action*>::iterator& it)
{
    delete *it;
    it = _actions.erase(it);
}
