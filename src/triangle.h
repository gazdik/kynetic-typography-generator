/*
 * triangle.h
 *
 *  Created on: Nov 19, 2016
 *      Author: gazdik
 */

#ifndef SRC_TRIANGLE_H_
#define SRC_TRIANGLE_H_

#include <node.h>
#include <GLProgram.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Triangle : public Node
{
public:
    Triangle();
    virtual ~Triangle();

    virtual void update();

protected:

    void initBuffers();
    void draw(const glm::mat4 & transform);

public:

    struct Point {
        GLfloat position[3];
        GLfloat color[3];
    };

private:

    GLProgram *_program;

    glm::mat4 _size;

    GLuint _VBO, _VAO;
    GLuint _uTransform, _uColor, _uAlpha;
    GLuint _uSize;
    GLuint _aPosition;
};

#endif /* SRC_TRIANGLE_H_ */
