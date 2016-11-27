/*
 * geometricshape.h
 *
 *  Created on: Nov 27, 2016
 *      Author: gazdik
 */

#ifndef SRC_GEOMETRICSHAPE_H_
#define SRC_GEOMETRICSHAPE_H_

#include "node.h"

class GeometricShape: public Node
{
public:
    struct Point {
        GLfloat position[3];
    };

    GeometricShape();
    virtual ~GeometricShape();

protected:
    void initBuffers();
    void draw(const glm::mat4 & transform);
    virtual void update();

protected:
    GLProgram *_program;

    glm::mat4 _size;

    GLuint _VBO = 0, _VAO = 0, _EBO = 0;
    GLuint _uTransform = -1, _uColor = -1, _uAlpha = -1;
    GLuint _uSize = -1;
    GLuint _aPosition = -1;
    GLuint _numVertices = 0;

public:
};

class Square: public GeometricShape
{
public:
    Square();
    Square(float width, float height);
    virtual ~Square();

private:
    void bufferData();
};

class Triangle: public GeometricShape
{
public:
    Triangle();
    Triangle(float width, float height);
    virtual ~Triangle();

private:
    void bufferData();
};

class Cube: public GeometricShape
{
public:
    Cube();
    Cube(float width, float height, float depth);
    virtual ~Cube();

private:
    void bufferData();
};

#endif /* SRC_GEOMETRICSHAPE_H_ */
