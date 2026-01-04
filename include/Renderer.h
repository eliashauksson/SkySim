// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;
};

struct DrawCommand {
  GLenum mode;
  size_t vertexCount;
  size_t offset;
};

class Renderer {
public:
  Renderer(int simWidth, int simHeight, int windowWidth, int windowHeight);
  ~Renderer();

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  void setWindowSize(int width, int height);

  void drawLine(const glm::vec2 &start, const glm::vec2 &end,
                float thicknessPixels = 1.0f,
                const glm::vec3 &color = {1.0f, 1.0f, 1.0f});

  void flush();

private:
  int simWidth_, simHeight_, windowWidth_, windowHeight_;

  std::vector<Vertex> vertices_;
  std::vector<DrawCommand> drawCommands_;

  GLuint vao_, vbo_;
  GLuint shaderProgram_;

  glm::vec2 simToNDC_(const glm::vec2 &simPos) const;
  glm::vec2 NDCToSim_(const glm::vec2 &NDCPos) const;

  void initGL_();
  GLuint loadShader_(const std::string &path, GLenum shaderType);
  void createShaderProgram_(const std::string &vertPath,
                            const std::string &fragPath);
};

#endif // RENDERER_H
