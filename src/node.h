#ifndef NODE_H
#define NODE_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>

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
     * Run action on this node
     * @param action
     */
    void runAction(Action *action);

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
    void setAlpha(float alpha);
    void setContentSize(float width, float height);
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
    glm::vec3 getRotation();
    float getAlpha();
    glm::vec3 getColor();
    bool isVisible();

protected:

    /**
     * Initialize OpenGL buffers
     */
    virtual void initBuffers() = 0;

    /**
     * Bind vertex array object, set uniforms and call glDraw
     * @param transform model-view-projection matrix
     */
    virtual void draw(const glm::mat4 & transform) = 0;

    glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);  ///< Position on x,y and z-axis
    glm::vec3 _scale = glm::vec3(1.0, 1.0, 1.0);             ///< Scaling factor on x and y axes
    glm::vec3 _rotation;
    float _alpha;                 ///< Alpha value
    glm::vec3 _color = glm::vec3(0.0f, 0.0f, 0.0f);     ///< Node color
    bool _visible = true;         ///< Visibility

    float _width = 1.0f;
    float _height = 1.0f;

    glm::mat4 _modelViewMatrix;   ///< ModelView transformation matrix

    std::vector<Node *> _children;  ///< Children nodes
};

#endif // NODE_H
