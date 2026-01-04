// main.cpp
#include "Renderer.h"
#include "Window.h"

int main() {
  Window window;

  int simulationWidth = 100;
  int simulationHeight = 100;

  Renderer renderer(simulationWidth, simulationHeight, window.getWidth(),
                    window.getHeight());
  window.setRenderer(&renderer);

  while (!window.shouldClose()) {
    window.clear();

    renderer.drawLine({20, 20}, {80, 80});

    renderer.flush();

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}
