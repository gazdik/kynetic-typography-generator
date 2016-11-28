#ifndef NODE_H
#define NODE_H

#include "GLProgram.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <set>

class Action;

class Node
{
public:
    Node();
    virtual ~Node();

    virtual void update();

    /**
     * Render the node and all children
     * @param parentTransform Transformation matrix of a parent node
     */
    virtual void render(const glm::mat4 & parentTransform);

    /**
     * Add child node
     * @param child
     */
    void addChild(Node *child);

    /**
     * Remove a reference to current node from it's parent
     */
    void removeReferenceFromParent();

    /**
     * Set the node's parent
     */
    void setParent(Node *parent);

    /**
     * Remove a reference to the child node
     * @param node
     */
    void removeChildReference(Node *node);

    /**
     * Run action on this node
     * @param action
     */
    void runAction(float delay, Action *action);

    void setPosition(float x, float y, float z = 0.0f);
    void setPosition(const glm::vec3 &position);
    void setScale(float scale);
    void setScale(float scaleX, float scaleY, float scaleZ);
    void setScale(const glm::vec3 & scale);
    void setXRotation(float rotation);
    void setYRotation(float rotation);
    void setZRotation(float rotation);
    void setRotation(const glm::vec3 & rotation);
    void setVisible(bool visible);
    void ignoreAnchorPointForPositioning(bool ignore);
    void setAlpha(float alpha);
    void setContentSize(float x, float y, float z = 0.0f);
    void setContentSize(const glm::vec3 & contentSize);
    void setAnchorPoint(const glm::vec3 & anchorPoint);
    void setAnchorPoint(float x, float y, float z = 0.0);
    void setColor(const glm::vec3 & color);
    void setColor(float red, float green, float blue);

    glm::vec3 getPosition();
    float getPositionX();
    float getPositionY();
    float getPositionZ();
    glm::vec3 getScale();
    float getScaleX();
    float getScaleY();
    float getScaleZ();
    float getXRotation();
    float getYRotation();
    float getZRotation();
    glm::vec3 getAnchorPoint();
    glm::vec3 getContentSize();
    glm::vec3 getRotation();
    float getAlpha();
    glm::vec3 getColor();
    bool isVisible();

protected:

    /**
     * Bind vertex array object, set uniforms and call glDraw
     * @param transform model-view-projection matrix
     */
    virtual void draw(const glm::mat4 & transform) = 0;

    glm::vec3 _position { 0.0f, 0.0f, 0.0f };   ///< Position on x,y and z-axis
    glm::vec3 _scale { 1.0, 1.0, 1.0 };         ///< Scaling factor on x,y and z-axis
    glm::vec3 _rotation { 0.0f, 0.0f, 0.0f };   ///< Rotation around x, y and z-axis
    glm::vec3 _color { 0.0f, 0.0f, 0.0f };      ///< Node color
    glm::vec3 _anchorPoint { 0.5f, 0.5f, 0.5f };
    glm::vec3 _contentSize { 0.0f, 0.0f, 0.0f };
    float _alpha;                               ///< Alpha value
    bool _ignoreAnchorForPositioning = false;
    bool _visible = true;                       ///< Visibility


    glm::mat4 _modelViewMatrix;   ///< ModelView transformation matrix

    std::set<Node *> _children;  ///< Children nodes
    Node *_parent = nullptr;
};

#endif // NODE_H
