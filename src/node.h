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

    void setPosition(float x, float y);
    void setPosition(glm::vec2 position);
    void setScale(float scale);
    void setScale(float scaleX, float scaleY);
    void setScale(const glm::vec2 & scale);
    void setRotation(float rotation);
    void setVisible(bool visible);
    void setAlpha(float alpha);
    void setContentSize(float width, float height);
    void setColor(const glm::vec3 & color);
    void setColor(float red, float green, float blue);

    glm::vec2 getPosition();
    float getPositionX();
    float getPositionY();
    glm::vec2 getScale();
    float getScaleX();
    float getScaleY();
    float getRotation();
    float getAlpha();
    glm::vec3 getColor();
    bool isVisible();

protected:

    /**
     * Initialize OpenGL buffers
     */
    virtual void initBuffers() = 0;

    /**
     * Set uniforms and draw the node
     * @param transform
     */
    virtual void draw(const glm::mat4 & transform) = 0;

    float _positionX = 0.0f;      ///< Position on x-axis
    float _positionY = 0.0f;      ///< Position on y-axis
    float _positionZ = 0.0f;      ///< Position on z-axis
    glm::vec2 _scale = glm::vec2(1.0, 1.0);             ///< Scaling factor on x and y axes
    float _rotation = 0.0f;       ///< Rotation angle
    float _alpha;                 ///< Alpha value
    glm::vec3 _color = glm::vec3(0.0f, 0.0f, 0.0f);     ///< Node color
    bool _visible = true;         ///< Visibility

    float _width = 1.0f;
    float _height = 1.0f;

    glm::mat4 _modelViewMatrix;   ///< ModelView transformation matrix

    std::vector<Node *> _children;  ///< Children nodes
};

#endif // NODE_H
