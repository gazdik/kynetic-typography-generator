#include "node.h"

#include "actionmanager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Node::Node()
{
    setAlpha(1.0);
}

void Node::render(const glm::mat4& parentTransform)
{
    update();

    if (!_visible)
        return;

    glm::mat4 transform = parentTransform * _modelViewMatrix;
    draw(transform);

    for (auto & child: _children)
        child->render(transform);
}

void Node::addChild(Node* child)
{
    _children.push_back(child);
    setAlpha(_alpha);
}

void Node::setPosition(float x, float y)
{
    _positionX = x;
    _positionY = y;
}

void Node::setPosition(glm::vec2 position)
{
    _positionX = position.x;
    _positionY = position.y;
}

void Node::setScale(float scale)
{
    _scale.x = _scale.y = scale;
}

void Node::setScale(float scaleX, float scaleY)
{
    _scale.x = scaleX;
    _scale.y = scaleY;
}

void Node::setRotation(float rotation)
{
    _rotation = rotation;
}

void Node::setVisible(bool visible)
{
    _visible = visible;
}

glm::vec2 Node::getPosition()
{
    glm::vec2 position;
    position.x = _positionX;
    position.y = _positionY;

    return position;
}

float Node::getPositionX()
{
    return _positionX;
}

float Node::getPositionY()
{
    return _positionY;
}

float Node::getScaleX()
{
    return _scale.x;
}

float Node::getScaleY()
{
    return _scale.y;
}

float Node::getRotation()
{
    return _rotation;
}

void Node::update()
{
    glm::mat4 modelViewMatrix;
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(_positionX, _positionY, _positionZ));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(_scale.x, _scale.y, 1.0));

    _modelViewMatrix = modelViewMatrix;
}

bool Node::isVisible()
{
    return _visible;
}

Node::~Node()
{
}

void Node::setContentSize(float width, float height)
{
    _width = width;
    _height = height;
}

void Node::runAction(Action* action)
{
    ActionManager::getInstance()->addAction(action, this);
}

void Node::setAlpha(float alpha)
{
    _alpha = alpha;
}

float Node::getAlpha()
{
    return _alpha;
}

void Node::setColor(const glm::vec3& color)
{
    _color = color;
}

void Node::setColor(float red, float green, float blue)
{
    _color.x = red;
    _color.y = green;
    _color.z = blue;
}

glm::vec3 Node::getColor()
{
    return _color;
}

glm::vec2 Node::getScale()
{
    return _scale;
}

void Node::setScale(const glm::vec2& scale)
{
    _scale = scale;
}
