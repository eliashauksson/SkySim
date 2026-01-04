// Renderer.cpp
#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Renderer::Renderer(int simWidth, int simHeight, int windowWidth,
                   int windowHeight)
    : simWidth_(simWidth), simHeight_(simHeight), windowWidth_(windowWidth),
      windowHeight_(windowHeight), vao_(0), vbo_(0), shaderProgram_(0) {
  initGL_();
  createShaderProgram_("shaders/basic.vert", "shaders/basic.frag");
}

Renderer::~Renderer() {
  if (vbo_) {
    glDeleteBuffers(1, &vbo_);
  }
  if (vao_) {
    glDeleteVertexArrays(1, &vao_);
  }
  if (shaderProgram_) {
    glDeleteProgram(shaderProgram_);
  }
}

void Renderer::setWindowSize(int width, int height) {
  windowWidth_ = width;
  windowHeight_ = height;
}

void Renderer::drawLine(const glm::vec2 &start, const glm::vec2 &end,
                        float thicknessPixels, const glm::vec3 &color) {
  glm::vec2 dir = end - start;
  if (glm::length(dir) < 1e-6f) {
    return;
  }

  glm::vec2 perpendicular = glm::normalize(glm::vec2(-dir.y, dir.x));

  float thicknessSimX = thicknessPixels * simWidth_ / (2.0f * windowWidth_);
  float thicknessSimY = thicknessPixels * simHeight_ / (2.0f * windowHeight_);

  glm::vec2 offset = perpendicular * glm::vec2(thicknessSimX, thicknessSimY);

  glm::vec2 v0 = start + offset;
  glm::vec2 v1 = end + offset;
  glm::vec2 v2 = end - offset;
  glm::vec2 v3 = start - offset;

  size_t offset_idx = vertices_.size();
  vertices_.push_back({simToNDC_(v0), color});
  vertices_.push_back({simToNDC_(v1), color});
  vertices_.push_back({simToNDC_(v2), color});
  vertices_.push_back({simToNDC_(v2), color});
  vertices_.push_back({simToNDC_(v3), color});
  vertices_.push_back({simToNDC_(v0), color});

  drawCommands_.push_back({GL_TRIANGLES, 6, offset_idx});
}

void Renderer::flush() {
  if (vertices_.empty()) {
    return;
  }

  glUseProgram(shaderProgram_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
               vertices_.data(), GL_DYNAMIC_DRAW);

  for (const auto &cmd : drawCommands_) {
    glDrawArrays(cmd.mode, cmd.offset, cmd.vertexCount);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glUseProgram(0);

  vertices_.clear();
  drawCommands_.clear();
}

glm::vec2 Renderer::simToNDC_(const glm::vec2 &simPos) const {
  return glm::vec2((simPos.x - simWidth_ * 0.5f) / (simWidth_ * 0.5f),
                   (simPos.y - simHeight_ * 0.5f) / (simHeight_ * 0.5f));
}

glm::vec2 Renderer::NDCToSim_(const glm::vec2 &NDCPos) const {
  return glm::vec2(NDCPos.x * simWidth_ * 0.5f + simWidth_ * 0.5f,
                   NDCPos.y * simHeight_ * 0.5f + simHeight_ * 0.5f);
}

void Renderer::initGL_() {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  // position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));

  // color
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, color));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

GLuint Renderer::loadShader_(const std::string &path, GLenum shaderType) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open shader: " + path);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string source = buffer.str();
  const char *src = source.c_str();

  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(shader, 512, nullptr, log);
    throw std::runtime_error("Shader compilation failed: " + std::string(log));
  }

  return shader;
}

void Renderer::createShaderProgram_(const std::string &vertPath,
                                    const std::string &fragPath) {
  GLuint vertShader = loadShader_(vertPath, GL_VERTEX_SHADER);
  GLuint fragShader = loadShader_(fragPath, GL_FRAGMENT_SHADER);

  shaderProgram_ = glCreateProgram();
  glAttachShader(shaderProgram_, vertShader);
  glAttachShader(shaderProgram_, fragShader);
  glLinkProgram(shaderProgram_);

  GLint success;
  glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(shaderProgram_, 512, nullptr, log);
    throw std::runtime_error("Shader linking failed: " + std::string(log));
  }

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
}
