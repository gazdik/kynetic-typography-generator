/*
 * GLView.h
 *
 *  Created on: Nov 12, 2016
 *      Author: gazdik
 */

#ifndef SRC_GLVIEW_H_
#define SRC_GLVIEW_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

class GLView
{
public:
  /**
   * Create full-screen OpenGL view
   * @param viewName
   */
  GLView(const std::string & viewName);

  /**
   * Create a window of the given size
   * @param viewName
   * @param width
   * @param height
   */
  GLView(const std::string & viewName, int width, int height);

  ~GLView();

  /**
   * Swap the front and back buffer.
   */
  void swapBuffers();

  /**
   * Get width of the view
   * @return
   */
  int getWidth();

  /**
   * Get height of the view
   * @return
   */
  int getHeight();

  /**
   * Get the window.
   * @return
   */
  GLFWwindow * getWindow() const;

  /**
   * Mouse button callback.
   * @param button  The mouse button that was pressed or released.
   * @param action  One of GLFW_PRESS or GLFW_RELEASE.
   * @param mods    Bit field describing which modifier keys were held down.
   */
  void setMouseButtonCB(std::function<void(int, int, int)> & callback);

  /**
   * Set keyboard key callback.
   * @param key     The keyboard that was pressed or released.
   * @param action  GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
   * @param mods    Bit field describing which modifier keys were held down.
   */
  void setKeyPressCB(std::function<void(int, int, int)> & callback);

  /**
   * Set cursor position callback.
   * @param x      The new cursor x-coordinate, relative to the left edge.
   * @param y      The new cursor y-coordinate, relative to the top edge.
   */
  void setMouseMoveCB(std::function<void(double, double)> & callback);


protected:
  friend class GLViewInputHandler;

  /**
   * Mouse button callback function.
   * @param window  The window that received the event.
   * @param button  The mouse button that was pressed or released.
   * @param action  One of GLFW_PRESS or GLFW_RELEASE.
   * @param mods    Bit field describing which modifier keys were held down.
   */
  void onMouseButton(GLFWwindow *window, int button, int action, int mods);

  /**
   * Cursor position callback function.
   * @param window The window that received the event.
   * @param x      The new cursor x-coordinate, relative to the left edge.
   * @param y      The new cursor y-coordinate, relative to the top edge.
   */
  void onMouseMove(GLFWwindow *window, double x, double y);

  /**
   * Keyboard key callback function.
   * @param window    The window that received the event.
   * @param key       The keyboard that was pressed or released.
   * @param scancode  The system-specific scancode of the key.
   * @param action    GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
   * @param mods      Bit field describing which modifier keys were held down.
   */
  void onKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods);

  /**
   * Window resize callback function.
   * @param window  The window that was resized.
   * @param width   The new width of the window.
   * @param height  The new height of the window.
   */
  void onWindowResize(GLFWwindow *window, int width, int height);

  /**
   * Framebuffer resize callback function.
   * @param window  The window whose framebuffer was resized
   * @param width   The new width of the framebuffer
   * @param height  The new height of the framebuffer
   */
  void onFramebufferResize(GLFWwindow *window, int width, int height);

  /**
   * Error callback function.
   * @param errorID
   * @param description
   */
  void onError(int error, const char* description);

private:
  void initWithDimension(const std::string & viewName, float width, float height);
  void initWithFullscreen(const std::string & viewName);
  void initGlew();
  /**
   * Set the viewport
   * @param x     x-coordinate of the lower left corner of the viewport rectangle.
   * @param y     y-coordinate of the lower left corner of the viewport rectangle.
   * @param width   Width of the viewport.
   * @param height  Height of the viewport.
   */
  void setViewport();

private:
  GLint _windowWidth;
  GLint _windowHeight;
  std::string _viewName;

  GLFWwindow *_window = nullptr;
  GLFWmonitor *_monitor = nullptr;

  /**
   * Keyboard key callback.
   * @param key     The keyboard that was pressed or released.
   * @param action  GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
   * @param mods    Bit field describing which modifier keys were held down.
   */

  std::function<void(int, int, int)> _onKeyPressCB;

  /**
   * Cursor position callback.
   * @param x      The new cursor x-coordinate, relative to the left edge.
   * @param y      The new cursor y-coordinate, relative to the top edge.
   */
  std::function<void(double, double)> _onMouseMoveCB;

  /**
   * Mouse button callback.
   * @param button  The mouse button that was pressed or released.
   * @param action  One of GLFW_PRESS or GLFW_RELEASE.
   * @param mods    Bit field describing which modifier keys were held down.
   */
  std::function<void(int, int, int)> _onMouseButtonCB;
};

class GLViewInputHandler
{
public:
  /**
   * Set GLView instance
   * @param view
   */
  static void setGLView(GLView *view);

  /**
   * Mouse button callback function.
   * @param window  The window that received the event.
   * @param button  The mouse button that was pressed or released.
   * @param action  One of GLFW_PRESS or GLFW_RELEASE.
   * @param mods    Bit field describing which modifier keys were held down.
   */
  static void onMouseButton(GLFWwindow *window, int button, int action, int mods);

  /**
   * Cursor position callback function.
   * @param window The window that received the event.
   * @param x      The new cursor x-coordinate, relative to the left edge.
   * @param y      The new cursor y-coordinate, relative to the top edge.
   */
  static void onMouseMove(GLFWwindow *window, double x, double y);

  /**
   * Keyboard key callback function.
   * @param window    The window that received the event.
   * @param key       The keyboard that was pressed or released.
   * @param scancode  The system-specific scancode of the key.
   * @param action    GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
   * @param mods      Bit field describing which modifier keys were held down.
   */
  static void onKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods);

  /**
   * Window resize callback function.
   * @param window  The window that was resized.
   * @param width   The new width of the window.
   * @param height  The new height of the window.
   */
  static void onWindowResize(GLFWwindow *window, int width, int height);

  /**
   * Framebuffer resize callback function.
   * @param window  The window whose framebuffer was resized
   * @param width   The new width of the framebuffer
   * @param height  The new height of the framebuffer
   */
  static void onFramebufferResize(GLFWwindow *window, int width, int height);

  /**
   * Error callback function.
   * @param errorID
   * @param description
   */
  static void onError(int error, const char* description);

private:
  static GLView *_view;
};


#endif /* SRC_GLVIEW_H_ */
