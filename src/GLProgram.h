/*
 * Shader.h
 *
 *  Created on: Oct 16, 2016
 *      Author: gazdik
 */

#ifndef SRC_GLPROGRAM_H_
#define SRC_GLPROGRAM_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLProgram
{
public:
  GLProgram() {}
  GLProgram(const std::string & vertexSourcePath, const std::string & fragmentSourcePath);
  GLProgram(const GLchar *vertexByteArray, const GLchar *fragmentByteArray);

  bool initWithSourceFiles(const std::string & vertexSourcePath,
                           const std::string & fragmentByteArray);
  bool initWithByteArrays(const GLchar *vertexByteArray,
                          const GLchar *fragmentByteArray);

  ~GLProgram();

  /**
   * Associate a generic vertex attribute index with a named attribute value.
   * It means you can set location of uniforms from cpp program instead specify
   * it explicitly in GLSL program or let compiler to set locations (it can boost performance).
   * @param attributeName Name of the attribute variable
   * @param index The index of a generic vertex attribute to be bound
   */
  void bindAttribLocation(const std::string &attributeName, GLint index) const;

  /**
   * Get a location of an attribute variable
   * @param attributeName Name of the attribute variable
   * @return The location of an attribute variable
   */
  GLint getAttribLocation(const std::string &attributeName) const;

  /**
   * Get a location of a uniform variable
   * @param uniformName The name of the uniform variable
   * @return The location of a uniform variable
   */
  GLint getUniformLocation(const std::string &uniformName) const;

  /**
   * Set the value of a uniform variable of type int
   * @param uniformName
   * @param u1
   */
  void setUniform1i(GLint location, GLint u1) const;
  /**
   * Set the value of a uniform variable of type ivec2
   * @param uniformName
   * @param u1
   * @param u2
   */
  void setUniform2i(GLint location, GLint u1, GLint u2) const;
  /**
   * Set the value of a uniform variable of type ivec3
   * @param uniformName
   * @param u1
   * @param u2
   * @param u3
   */
  void setUniform3i(GLint location, GLint u1, GLint u2, GLint u3) const;
  /**
   * Set the value of a uniform variable of type ivec4
   * @param uniformName
   * @param u1
   * @param u2
   * @param u3
   * @param u4
   */
  void setUniform4i(GLint location, GLint u1, GLint u2, GLint u3, GLint u4) const;
  /**
   * Set the value of a uniform variable of type float
   * @param uniformName
   * @param u1
   */
  void setUniform1f(GLint location, GLfloat u1);
  /**
   * Set the value of a uniform variable of type vec2
   * @param uniformName
   * @param u1
   * @param u2
   */
  void setUniform2f(GLint location, GLfloat u1, GLfloat u2);
  /**
   * Set the value of a uniform variable of type vec3
   * @param uniformName
   * @param u1
   * @param u2
   * @param u3
   */
  void setUniform3f(GLint location, GLfloat u1, GLfloat u2, GLfloat u3);
  /**
   * Set the value of a uniform variable of type vec4
   * @param uniformName
   * @param u1
   * @param u2
   * @param u3
   */
  void setUniform4f(GLint location, GLfloat u1, GLfloat u2, GLfloat u3, GLfloat u4);
  /**
   * Set the value of a uniform variable of type mat2
   * @param uniformName
   * @param matrixArray
   * @param numberOfMatrices
   */
  void setUniformMatrix2fv(GLint location, const GLfloat * matrixArray,
                           unsigned int numberOfMatrices);
  /**
   * Set the value of a uniform variable of type mat3
   * @param uniformName
   * @param matrixArray
   * @param numberOfMatrices
   */
  void setUniformMatrix3fv(GLint location, const GLfloat * matrixArray,
                           unsigned int numberOfMatrices);
  /**
   * Set the value of uniform variable of type mat4
   * @param uniformName
   * @param matrixArray
   * @param numberOfMatrices
   */
  void setUniformMatrix4fv(GLint location, const GLfloat * matrixArray,
                           unsigned int numberOfMatrices);

  /**
   * Use this program
   */
  void use();

private:
  GLint _program = 0; // the program ID
};

#endif /* SRC_GLPROGRAM_H_ */
