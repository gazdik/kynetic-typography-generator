#include "text.h"

#include <stdexcept>

Text::Text(std::string str, std::string fontName)
{
    _string = str;
    font = FontCache::getInstance()->font(fontName);

    _program = new GLProgram;
    _program->initWithSourceFiles(
                "shaders/text.vs",
                "shaders/text.fs");
    initBuffers();
}

Text::~Text()
{
}

void Text::initBuffers()
{
    _uTransform = _program->getUniformLocation("transform");
    _uScale = _program->getUniformLocation("scale");
    _uColor = _program->getUniformLocation("color");
    _uAlpha = _program->getUniformLocation("alpha");
    _uPen = _program->getUniformLocation("pen");

    _aPosition = _program->getAttribLocation("position");
    _aNormal = _program->getAttribLocation("normal");
}

void Text::draw(const glm::mat4 &transform)
{
    _program->use();

    _program->setUniformMatrix4fv(_uTransform, glm::value_ptr(transform), 1);
    _program->setUniformMatrix4fv(_uScale, glm::value_ptr(_scaleMatrix), 1);
    _program->setUniform3f(_uColor, _color.x, _color.y, _color.z);
    _program->setUniform1f(_uAlpha, _alpha);

    font->ShaderLocations(_aPosition, _aNormal, _uPen);
    //font->FaceSize(70);

    simpleLayout.SetFont(font);
    simpleLayout.SetLineLength(600.0f);
    simpleLayout.Render(_string.c_str(), -1, FTPoint(), FTGL::RENDER_FRONT);
}

void Text::update()
{
    Node::update();

    glm::mat4 identity;
    _scaleMatrix = glm::scale(identity, glm::vec3(_scale.x, _scale.y, 1.0f));
}
