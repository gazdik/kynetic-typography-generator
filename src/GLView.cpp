/*
 * GLView.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: gazdik
 */

#include "GLView.h"

#include <macros.h>

#include <cstring>
#include <exception>

GLView::GLView(const std::string& viewName)
{
  GLViewInputHandler::setGLView(this);

  glfwSetErrorCallback(GLViewInputHandler::onError);
  glfwInit();

  initWithFullscreen(viewName);
}

GLView::GLView(const std::string& viewName, int width, int height)
{
  GLViewInputHandler::setGLView(this);

  glfwSetErrorCallback(GLViewInputHandler::onError);
  glfwInit();

  initWithDimension(viewName, width, height);
}

GLView::~GLView()
{
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void GLView::initWithDimension(const std::string& viewName, float width,
    float height)
{
  _viewName = viewName;
  _viewWidth = width;
  _viewHeight = height;

  glfwWindowHint(GLFW_SAMPLES, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glewExperimental = GL_TRUE;

  _window = glfwCreateWindow(width, height, _viewName.c_str(), _monitor, nullptr);
  glfwMakeContextCurrent(_window);

  // Set callbacks for input events.
  glfwSetMouseButtonCallback(_window, GLViewInputHandler::onMouseButton);
  glfwSetCursorPosCallback(_window, GLViewInputHandler::onMouseMove);
  glfwSetKeyCallback(_window, GLViewInputHandler::onKeyPress);
  glfwSetFramebufferSizeCallback(_window, GLViewInputHandler::onFramebufferResize);
  glfwSetWindowSizeCallback(_window, GLViewInputHandler::onWindowResize);

  initGlew();
}

void GLView::initWithFullscreen(const std::string& viewName)
{
  _monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *videoMode = glfwGetVideoMode(_monitor);

  initWithDimension(viewName, videoMode->width, videoMode->height);
}

void GLView::swapBuffers()
{
  if (_window)
    glfwSwapBuffers(_window);
}

void GLView::onWindowResize(GLFWwindow* window, int width, int height)
{
  UNUSED(window);

  _viewWidth = width;
  _viewHeight = height;
  setViewport(0, 0, _viewWidth, _viewHeight);
}

void GLView::onFramebufferResize(GLFWwindow* window, int width, int height)
{
  UNUSED(window);

  _viewWidth = width;
  _viewHeight = height;
  setViewport(0, 0, _viewWidth, _viewHeight);
}

void GLView::initGlew()
{
  GLenum result = glewInit();

  if (result != GLEW_OK)
    throw std::runtime_error((char *) glewGetErrorString(result));
}

void GLView::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
  UNUSED(window);
  if (_onMouseButtonCB)
    _onMouseButtonCB(button, action, mods);
}

void GLView::onMouseMove(GLFWwindow* window, double x, double y)
{
  UNUSED(window);
  if (_onMouseMoveCB)
    _onMouseMoveCB(x, y);
}

void GLView::onKeyPress(GLFWwindow* window, int key, int scancode, int action,
    int mods)
{
  UNUSED(window);
  UNUSED(scancode);
  if (_onKeyPressCB)
    _onKeyPressCB(key, action, mods);
}

void GLView::setMouseButtonCB(std::function<void(int, int, int)>& callback)
{
  _onMouseButtonCB = callback;
}

void GLView::setKeyPressCB(std::function<void(int, int, int)>& callback)
{
  _onKeyPressCB = callback;
}

void GLView::setMouseMoveCB(std::function<void(double, double)>& callback)
{
  _onMouseMoveCB = callback;
}

int GLView::getWidth()
{
  return _viewWidth;
}

int GLView::getHeight()
{
  return _viewHeight;
}

GLFWwindow* GLView::getWindow() const
{
  return _window;
}

void GLView::onError(int error, const char* description)
{
  std::fprintf(stderr, "GLFW Error #%d: %s", error, description);
}

void GLView::setViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);
}

////////////////////////////////////////////////////////////////////////////////

GLView * GLViewInputHandler::_view = nullptr;

void GLViewInputHandler::setGLView(GLView* view)
{
  _view = view;
}

void GLViewInputHandler::onMouseButton(GLFWwindow* window, int button,
    int action, int mods)
{
  if (_view)
    _view->onMouseButton(window, button, action, mods);
}

void GLViewInputHandler::onMouseMove(GLFWwindow* window, double x, double y)
{
  if (_view)
    _view->onMouseMove(window, x, y);
}

void GLViewInputHandler::onKeyPress(GLFWwindow* window, int key, int scancode,
    int action, int mods)
{
  if (_view)
    _view->onKeyPress(window, key, scancode, action, mods);
}

void GLViewInputHandler::onWindowResize(GLFWwindow* window, int width,
    int height)
{
  if (_view)
    _view->onWindowResize(window, width, height);
}

void GLViewInputHandler::onFramebufferResize(GLFWwindow* window, int width,
    int height)
{
  if (_view)
    _view->onFramebufferResize(window, width, height);
}

void GLViewInputHandler::onError(int error, const char* description)
{
  if (_view)
    _view->onError(error, description);
}
