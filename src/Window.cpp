// Window.cpp
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

int Window::glfwRefCount_ = 0;

Window::Window(int width, int height, std::string title)
    : width_(width), height_(height), title_(title) {
  initGlfw_();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
  if (!window_) {
    terminateGlfw_();
    throw std::runtime_error("Failed to create GLFW window.");
  }

  glfwMakeContextCurrent(window_);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    terminateGlfw_();
    throw std::runtime_error("Failed to initialize GLAD.");
  }

  glfwSetWindowUserPointer(window_, this);
  glfwSetFramebufferSizeCallback(window_, glfwOnFrameBufferSize_);

  int fbWidth, fbHeight;
  glfwGetFramebufferSize(window_, &fbWidth, &fbHeight);
  width_ = fbWidth;
  height_ = fbHeight;
  glViewport(0, 0, width_, height_);
}

Window::~Window() {
  if (window_) {
    glfwDestroyWindow(window_);
    window_ = nullptr;
  }
  terminateGlfw_();
}

bool Window::shouldClose() const { return glfwWindowShouldClose(window_); }

void Window::clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void Window::pollEvents() const { glfwPollEvents(); }

void Window::swapBuffers() const { glfwSwapBuffers(window_); }

int Window::getWidth() const { return width_; }

int Window::getHeight() const { return height_; }

void Window::initGlfw_() {
  if (glfwRefCount_ == 0) {
    if (!glfwInit()) {
      throw std::runtime_error("GLFW initialization failed.");
    }
  }
  ++glfwRefCount_;
}

void Window::terminateGlfw_() {
  --glfwRefCount_;
  if (glfwRefCount_ == 0) {
    glfwTerminate();
  }
}

void Window::glfwOnFrameBufferSize_(GLFWwindow *window, int width, int height) {
  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if (!self) {
    return;
  }

  self->width_ = width;
  self->height_ = height;
  glViewport(0, 0, width, height);
}
