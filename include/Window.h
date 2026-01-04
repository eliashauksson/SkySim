// Window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <string>

struct GLFWwindow;
class Renderer;

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

  void setRenderer(Renderer* renderer);

  int getWidth() const;
  int getHeight() const;

private:
  int width_, height_;
  std::string title_;
  GLFWwindow *window_;

  static void initGlfw_();
  static void terminateGlfw_();
  static int glfwRefCount_;

  static void glfwOnFrameBufferSize_(GLFWwindow *window, int width, int height);

  Renderer* renderer_;
};

#endif // WINDOW_H
