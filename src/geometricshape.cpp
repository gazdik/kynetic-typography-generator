/*
 * geometricshape.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: gazdik
 */

#include "geometricshape.h"

GeometricShape::GeometricShape()
{
    _program = new GLProgram;
    _program->initWithSourceFiles("shaders/geometricshape.vs", "shaders/geometricshape.fs");
    initBuffers();
}

GeometricShape::~GeometricShape()
{
    delete _program;
}

void GeometricShape::draw(const glm::mat4& transform)
{
    _program->use();

    glBindVertexArray(_VAO);
    _program->setUniformMatrix4fv(_uTransform, glm::value_ptr(transform), 1);
    _program->setUniformMatrix4fv(_uSize, glm::value_ptr(_size), 1);
    _program->setUniform3f(_uColor, _color.x, _color.y, _color.z);
    _program->setUniform1f(_uAlpha, _alpha);

    glDrawElements(GL_TRIANGLES, _numVertices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void GeometricShape::initBuffers()
{
    _uTransform = _program->getUniformLocation("transform");
    _uSize = _program->getUniformLocation("size");
    _uColor = _program->getUniformLocation("color");
    _uAlpha = _program->getUniformLocation("alpha");
    _aPosition = _program->getAttribLocation("position");

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);
}

void GeometricShape::update()
{
    Node::update();

    glm::mat4 identity;
    _size = glm::scale(identity, glm::vec3(_contentSize.x, _contentSize.y, _contentSize.z));
}

static const GeometricShape::Point square_vertices[] {
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
};

static const GLuint square_indices[] {
        0, 1, 3,
        1, 2, 3,
};

Square::Square()
{
    _numVertices = sizeof(square_indices) / sizeof(GLuint);
    bufferData();
}

Square::~Square()
{
}

Square::Square(float width, float height) :
        Square()
{
    _contentSize.x = width;
    _contentSize.y = height;
}

void Square::bufferData()
{
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Point),
                          (void *) offsetof(Point, position));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static const GeometricShape::Point triangle_vertices[] {
        { 1.0f, 0.0f, 0.0f }, // Bottom Right
        { 0.0f, 0.0f, 0.0f }, // Bottom Left
        { 0.5f, 1.0f, 0.0f }, // Top
};

static const GLuint triangle_indices[] {
        0, 1, 2
};

Triangle::Triangle()
{
    _numVertices = sizeof(triangle_indices) / sizeof(GLuint);
    bufferData();
}

Triangle::~Triangle()
{
}

Triangle::Triangle(float width, float height) :
        Triangle()
{
    _contentSize.x = width;
    _contentSize.y = height;
}

void Triangle::bufferData()
{
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Point),
                          (void *) offsetof(Point, position));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

static const Cube::Point cube_vertices[] {
        // Front
        { 0.0f, 0.0f, 0.0f }, // Bottom Left
        { 1.0f, 0.0f, 0.0f }, // Bottom Right
        { 1.0f, 1.0f, 0.0f }, // Top Right
        { 0.0f, 1.0f, 0.0f }, // Top Left
        // Back
        { 1.0f, 0.0f, 1.0f }, // Bottom Right
        { 0.0f, 0.0f, 1.0f }, // Bottom Left
        { 1.0f, 1.0f, 1.0f }, // Top Right
        { 0.0f, 1.0f, 1.0f }, // Top Left
};

static const GLuint cube_indices[] {
        // Front
        0, 1, 3,
        1, 2, 3,
        // Right
        1, 2, 4,
        2, 4, 6,
        // Back
        4, 5, 7,
        4, 6, 7,
        // Left
        0, 3, 5,
        3, 5, 7,
        // Top
        2, 3, 7,
        2, 6, 7,
       // Bottom
        0, 1, 5,
        1, 4, 5,
};

Cube::Cube()
{
    _numVertices = sizeof(cube_indices) / sizeof(GLuint);
    bufferData();
}

Cube::~Cube()
{
}

Cube::Cube(float width, float height, float depth) :
        Cube()
{
    _contentSize.x = width;
    _contentSize.y = height;
    _contentSize.z = depth;
}

void Cube::bufferData()
{
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Point),
                          (void *) offsetof(Point, position));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
