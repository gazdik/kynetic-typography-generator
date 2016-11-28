#include "node.h"

#include "actionmanager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

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
    child->setParent(this);
    _children.insert(child);
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

    glm::vec3 position = _position;

    glm::vec3 anchorPointInPoints = (_anchorPoint * _contentSize);

    if (_ignoreAnchorForPositioning)
    {
        position += anchorPointInPoints;
    }

    anchorPointInPoints *= _scale;

    // Calc sin and cos for rotation matrix
    float sinx, cosx, siny, cosy, sinz, cosz;
    sinx = sinf(-glm::radians(_rotation.x));
    cosx = cosf(-glm::radians(_rotation.x));
    siny = sinf(-glm::radians(_rotation.y));
    cosy = cosf(-glm::radians(_rotation.y));
    sinz = sinf(-glm::radians(_rotation.z));
    cosz = cosf(-glm::radians(_rotation.z));

    // all axes at once
    position.x +=   cosy * cosz * -anchorPointInPoints.x
                  + cosy * -sinz * -anchorPointInPoints.y
                  + siny * -anchorPointInPoints.z;
    position.y +=   (-sinx * -siny * cosz + cosx * sinz) * -anchorPointInPoints.x
                  + (-sinx * -siny * -sinz + cosx * cosz) * -anchorPointInPoints.y
                  + -sinx * cosy * -anchorPointInPoints.z;
    position.z +=   (cosx * -siny * cosz + sinx * sinz) * -anchorPointInPoints.x
                  + (cosx * -siny * -sinz + sinx * cosz) * -anchorPointInPoints.y
                  + cosx * cosy * -anchorPointInPoints.z;
    // z-axis
//    position.x += cosz * -anchorPointInPoints.x + -sinz * -anchorPointInPoints.y;
//    position.y += sinz * -anchorPointInPoints.x +  cosz * -anchorPointInPoints.y;

    // Translate
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(position.x, position.y, position.z));

    // Rotate around x-axis
    modelViewMatrix = glm::rotate(modelViewMatrix, -glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    // Rotate around y-axis
    modelViewMatrix = glm::rotate(modelViewMatrix, -glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    // Rotate around z-axis
    modelViewMatrix = glm::rotate(modelViewMatrix, -glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Scale
    modelViewMatrix = glm::scale(modelViewMatrix, _scale);

    _modelViewMatrix = modelViewMatrix;
}

void Node::setContentSize(float x, float y, float z)
{
    _contentSize.x = x;
    _contentSize.y = y;
    _contentSize.z = z;
}

void Node::setContentSize(const glm::vec3& contentSize)
{
    _contentSize = contentSize;
}

glm::vec3 Node::getContentSize()
{
    return _contentSize;
}

void Node::setAnchorPoint(const glm::vec3& anchorPoint)
{
}

void Node::setAnchorPoint(float x, float y, float z)
{
    _anchorPoint.x = x;
    _anchorPoint.y = y;
    _anchorPoint.z = z;
}

glm::vec3 Node::getAnchorPoint()
{
    return _anchorPoint;
}

bool Node::isVisible()
{
    return _visible;
}

Node::~Node()
{
    removeReferenceFromParent();

    for (auto child: _children)
        delete child;
}

void Node::runAction(float delay, Action* action)
{
    ActionManager::getInstance()->addAction(
        new Sequence(
            new Delay(delay),
            action,
            nullptr
        ),
        this
    );
}

void Node::setAlpha(float alpha)
{
    _alpha = alpha;
    for (auto child: _children)
        child->setAlpha(alpha);
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

void Node::ignoreAnchorPointForPositioning(bool ignore)
{
    _ignoreAnchorForPositioning = ignore;
}

void Node::removeReferenceFromParent()
{
    if (_parent)
        _parent->removeChildReference(this);
}

void Node::setParent(Node* parent)
{
    _parent = parent;
}

void Node::removeChildReference(Node* node)
{
    auto it = _children.find(node);
    if (it != _children.end()) {
        _children.erase(it);
    }
}
