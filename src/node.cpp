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

void Node::setPosition(float x, float y, float z)
{
    _position.x = x;
    _position.y = y;
    _position.z = z;
}

void Node::setPosition(const glm::vec3 & position)
{
    _position = position;
}

void Node::setScale(float scale)
{
    _scale.x = _scale.y = _scale.z = scale;
}

void Node::setScale(float scaleX, float scaleY, float scaleZ)
{
    _scale.x = scaleX;
    _scale.y = scaleY;
    _scale.z = scaleZ;
}


void Node::setXRotation(float rotation)
{
    _rotation.x = rotation;
}

void Node::setYRotation(float rotation)
{
    _rotation.y = rotation;
}

void Node::setZRotation(float rotation)
{
    _rotation.z = rotation;
}

void Node::setRotation(const glm::vec3& rotation)
{
    _rotation = rotation;
}

void Node::setVisible(bool visible)
{
    _visible = visible;
}

glm::vec3 Node::getPosition()
{
    return _position;
}

float Node::getPositionX()
{
    return _position.x;
}

float Node::getPositionY()
{
    return _position.y;
}

float Node::getPositionZ()
{
    return _scale.z;
}


float Node::getScaleX()
{
    return _scale.x;
}

float Node::getScaleY()
{
    return _scale.y;
}

float Node::getScaleZ()
{
    return _scale.z;
}

float Node::getXRotation()
{
    return _rotation.x;
}

float Node::getYRotation()
{
    return _rotation.y;
}

float Node::getZRotation()
{
    return _rotation.z;
}

glm::vec3 Node::getRotation()
{
    return _rotation;
}

void Node::update()
{
    glm::mat4 modelViewMatrix;
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(_position.x, _position.y, _position.z));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(_scale.x, _scale.y, _scale.z));

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

glm::vec3 Node::getScale()
{
    return _scale;
}

void Node::setScale(const glm::vec3& scale)
{
    _scale = scale;
}

