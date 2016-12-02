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

typedef enum
{
    ALIGN_LEFT    = FTGL::ALIGN_LEFT,
    ALIGN_CENTER  = FTGL::ALIGN_CENTER,
    ALIGN_RIGHT   = FTGL::ALIGN_RIGHT,
    ALIGN_JUSTIFY = FTGL::ALIGN_JUSTIFY
} TextAlignment;

struct Point {
    float x;
    float y;
    Point(): x(0), y(0) {}
    Point(float x, float y): x(x), y(y) {}
};

class Text : public Node
{
public:
    Text(std::string str, std::string fontName = "Roboto-Regular");
    virtual ~Text();

    virtual void update();

    Point getDimensions();

    TextAlignment getAlignment() const;
    void setAlignment(TextAlignment getAlignment);

    float getLineLength() const;
    void setLineLength(float getLineLength);

    void setScale(float scale);

    /**
     * @brief Sets scale of text so that it has the specified width.
     * @param width desired width of the text
     */
    void setScaleForWidth(float width);

    /**
     * @brief Sets scale of text so that it has the specified height.
     * @param height desired height of the text
     */
    void setScaleForHeight(float height);

    float getLineSpacing() const;
    void setLineSpacing(float lineSpacing);

protected:

    void initBuffers();
    void draw(const glm::mat4 & transform);

private:

    TextAlignment _alignment = ALIGN_LEFT;
    float _lineLength = 1920.0f;
    float _lineSpacing = 1.0f;

    std::string _string;

    // Requested scale. The real scale stored in Node is modified to match
    // FTGL text units.
    float _reqScale = 1.0f;

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
