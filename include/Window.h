// Window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
  static inline constexpr int defaultWidth = 1024;
  static inline constexpr int defaultHeight = 768;
  static inline constexpr const char *defaultTitle = "SkySim";

  explicit Window(int width = defaultWidth, int height = defaultHeight,
                  const char *title = defaultTitle);
  ~Window();

  bool shouldClose() const;
  void clear() const;
  void pollEvents() const;
  void swapBuffers() const;

  int getWidth() const;
  int getHeight() const;

private:
  int width_;
  int height_;
  const char *title_;
  GLFWwindow *window_;

  static void glfwOnFrameBufferSize_(GLFWwindow *window, int width, int height);
};

#endif // WINDOW_H
