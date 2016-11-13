/*
 * Shader.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: gazdik
 */

#include "GLProgram.h"

using namespace std;

GLProgram::GLProgram(const std::string & vertexSourcePath, const std::string & fragmentSourcePath)
{
  initWithSourceFiles(vertexSourcePath, fragmentSourcePath);
}

GLProgram::~GLProgram()
{
  glDeleteProgram(_program);
}

GLProgram::GLProgram(const GLchar* vertexByteArray,
    const GLchar* fragmentByteArray)
{
  initWithByteArrays(vertexByteArray, fragmentByteArray);
}

void GLProgram::bindAttribLocation(const std::string& attributeName,
    GLint index) const
{
  glBindAttribLocation(_program, index, attributeName.c_str());
}

GLint GLProgram::getAttribLocation(const std::string& attributeName) const
{
  return glGetAttribLocation(_program, attributeName.c_str());
}

GLint GLProgram::getUniformLocation(const std::string& uniformName) const
{
  return glGetUniformLocation(_program, uniformName.c_str());
}

void GLProgram::use()
{
  glUseProgram(_program);
}

void GLProgram::setUniform1i(GLint location, GLint u1) const
{
  glUniform1i(location, u1);
}

void GLProgram::setUniform2i(GLint location, GLint u1,
    GLint u2) const
{
  glUniform2i(location, u1, u2);
}

void GLProgram::setUniform3i(GLint location, GLint u1, GLint u2,
    GLint u3) const
{
  glUniform3i(location, u1, u2, u3);
}

void GLProgram::setUniform4i(GLint location, GLint u1, GLint u2,
    GLint u3, GLint u4) const
{
  glUniform4i(location, u1, u2, u3, u4);
}

void GLProgram::setUniform1f(GLint location, GLfloat u1)
{
  glUniform1f(location, u1);
}

void GLProgram::setUniform2f(GLint location, GLfloat u1,
    GLfloat u2)
{
  glUniform2f(location, u1, u2);
}

void GLProgram::setUniform3f(GLint location, GLfloat u1,
    GLfloat u2, GLfloat u3)
{
  glUniform3f(location, u1, u2, u3);
}

void GLProgram::setUniform4f(GLint location, GLfloat u1,
    GLfloat u2, GLfloat u3, GLfloat u4)
{
  glUniform4f(location, u1, u2, u3, u4);

}

void GLProgram::setUniformMatrix2fv(GLint location,
    const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
  glUniformMatrix2fv(location, (GLsizei) numberOfMatrices, GL_FALSE, matrixArray);
}

void GLProgram::setUniformMatrix3fv(GLint location,
    const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
  glUniformMatrix3fv(location, (GLsizei) numberOfMatrices, GL_FALSE, matrixArray);
}

void GLProgram::setUniformMatrix4fv(GLint location,
    const GLfloat* matrixArray, unsigned int numberOfMatrices)
{
  glUniformMatrix4fv(location, (GLsizei) numberOfMatrices, GL_FALSE, matrixArray);
}

bool GLProgram::initWithSourceFiles(const std::string& vertexSourcePath,
    const std::string& fragmentSourcePath)
{
  string vertexCode;
  string fragmentCode;
  ifstream vShaderFile;
  ifstream fShaderFile;

  vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
  fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

  try {
    vShaderFile.open(vertexSourcePath);
    fShaderFile.open(fragmentSourcePath);

    stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (ifstream::failure &e) {
    cerr << "ERROR: Shader file not succesfully read" << endl;
    return false;
  }

  const GLchar *vShaderCode = vertexCode.c_str();
  const GLchar *fShaderCode = fragmentCode.c_str();

  return initWithByteArrays(vShaderCode, fShaderCode);
}


bool GLProgram::initWithByteArrays(const GLchar* vertexByteArray,
    const GLchar* fragmentByteArray)
{

  GLint vertex, fragment;
  GLint success;
  GLchar infoLog[100];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexByteArray, nullptr);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (not success)
  {
    glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    cerr << "ERROR: Vertex shader compilation failed: " << infoLog << endl;
    return false;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentByteArray, nullptr);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (not success)
  {
    glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    cerr << "ERROR: Fragment shader compilation failed: " << infoLog << endl;
    return false;
  }

  _program = glCreateProgram();
  glAttachShader(_program, vertex);
  glAttachShader(_program, fragment);
  glLinkProgram(_program);

  glGetProgramiv(_program, GL_LINK_STATUS, &success);
  if (not success) {
    glGetProgramInfoLog(_program, 512, nullptr, infoLog);
    cerr << "ERROR: Shader program linking failed" << endl;
    return false;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return true;
}
