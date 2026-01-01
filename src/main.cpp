// main.cpp
#include "Window.h"

int main() {
  Window window;

  while (!window.shouldClose()) {
    window.clear();

    // code

    window.swapBuffers();
    window.pollEvents();
  }
  
  return 0;
}
