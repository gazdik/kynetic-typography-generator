/*
 * triangle.cpp
 *
 *  Created on: Nov 19, 2016
 *      Author: gazdik
 */

#include "triangle.h"

#include <glm/gtc/type_ptr.hpp>

static const Triangle::Point vertices[] {
    { { 0.5f, -0.5f, 0.0f },  { 0.3f, 0.8f, 0.9f } },   // Bottom Right
    { { -0.5f, -0.5f, 0.0f }, { 0.1f, 0.4f, 0.8f } },  // Bottom Left
    { {  0.0f,  0.5f, 0.0f }, { 0.9f, 0.5f, 0.1f } }   // Top
};

Triangle::Triangle()
{
    _program = new GLProgram;
    _program->initWithSourceFiles("shaders/triangle.vs", "shaders/triangle.fs");
    initBuffers();
}

Triangle::~Triangle()
{
}

void Triangle::initBuffers()
{
    _uTransform = _program->getUniformLocation("transform");
    _uSize = _program->getUniformLocation("size");
    _uColor = _program->getUniformLocation("color");
    _uAlpha = _program->getUniformLocation("alpha");
    _aPosition = _program->getAttribLocation("position");

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    /*
     * Bind the Vertex Array Object first, then bind and set vertex buffer(s)
     * and attribute pointer(s)
     */
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glVertexAttribPointer(_aColor, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle::Point),
//                          (void *) offsetof(Point, color));
    glVertexAttribPointer(_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle::Point),
                          (void *) offsetof(Point, position));

    glEnableVertexAttribArray(0);
    /*
     * Note that this is allowed, the call to glVertexAttribPointer registered
     * VBO as the currently bound vertex buffer object so afterwards we can
     * safely unbind
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::draw(const glm::mat4& transform)
{
    _program->use();

    glBindVertexArray(_VAO);
    _program->setUniformMatrix4fv(_uTransform, glm::value_ptr(transform), 1);
    _program->setUniformMatrix4fv(_uSize, glm::value_ptr(_size), 1);
    _program->setUniform3f(_uColor, _color.x, _color.y, _color.z);
    _program->setUniform1f(_uAlpha, _alpha);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}

void Triangle::update()
{
    Node::update();

    glm::mat4 identity;
    _size = glm::scale(identity, glm::vec3(_width, _height, 1.0));
}
