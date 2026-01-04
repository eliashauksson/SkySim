// Window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <string>

struct GLFWwindow;

class Window {
public:
  Window(int width = 1024, int height = 768, std::string title = "SkySim");
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool shouldClose() const;
  void clear() const;
  void pollEvents() const;
  void swapBuffers() const;

  int getWidth() const;
  int getHeight() const;

private:
  int width_;
  int height_;
  std::string title_;
  GLFWwindow *window_;

  static void initGlfw_();
  static void terminateGlfw_();
  static int glfwRefCount_;

  static void glfwOnFrameBufferSize_(GLFWwindow *window, int width, int height);
};

#endif // WINDOW_H
