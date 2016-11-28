#ifndef TEXT_H
#define TEXT_H

#include "node.h"
#include "GLProgram.h"
#include "fontcache.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <FTGL/ftgl.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Text : public Node
{
public:
    Text(std::string str, std::string fontName = "Roboto-Regular");
    virtual ~Text();

    virtual void update();
protected:

    void initBuffers();
    void draw(const glm::mat4 & transform);

private:

    std::string _string;

    GLProgram *_program;

    glm::mat4 _scaleMatrix;

    FTFont *font;
    FTSimpleLayout simpleLayout;

    GLuint _uTransform, _uColor, _uAlpha;
    GLuint _uPen;
    GLuint _uScale;
    GLuint _aPosition;
    GLuint _aNormal;
};

#endif // TEXT_H
