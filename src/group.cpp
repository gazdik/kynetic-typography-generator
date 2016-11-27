/*
 * group.cpp
 *
 *  Created on: Nov 25, 2016
 *      Author: gazdik
 */

#include "group.h"

Group::Group()
{
    _ignoreAnchorForPositioning = true;
}

Group::~Group()
{
}

Group::Group(float width, float height, float depth) :
        Group()
{
    _contentSize.x = width;
    _contentSize.y = height;
    _contentSize.z = depth;
}

void Group::draw(const glm::mat4& transform)
{
}
