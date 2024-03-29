/*
 * group.h
 *
 *  Created on: Nov 25, 2016
 *      Author: gazdik
 */

#ifndef SRC_GROUP_H_
#define SRC_GROUP_H_

#include "node.h"

class Group: public Node
{
public:
    Group();
    Group(float width, float height, float depth = 0.0f);
    virtual ~Group();

protected:
    virtual void draw(const glm::mat4 & transform);
};

#endif /* SRC_GROUP_H_ */
