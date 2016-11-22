/*
 * actionmanager.h
 *
 *  Created on: Nov 21, 2016
 *      Author: gazdik
 */

#ifndef SRC_ACTIONMANAGER_H_
#define SRC_ACTIONMANAGER_H_

#include "action.h"
#include "node.h"

#include <set>

class ActionManager
{
public:
    static ActionManager * getInstance();
    virtual ~ActionManager();

    /**
     * Add the action that will be performed
     * @param action
     * @param node
     */
    void addAction(Action *action, Node *node);

    /**
     * Remove the action
     * @param action
     */
    void removeAction(Action *action);

    /**
     * Update all actions according to time
     * @param time Time in seconds
     */
    void update(float time);

protected:
    ActionManager();

private:

    void removeAction(std::set<Action *>::iterator & it);

    bool _firstUpdate = true;
    float _previousTime = 0.0f;
    std::set<Action *> _actions;
};

#endif /* SRC_ACTIONMANAGER_H_ */
