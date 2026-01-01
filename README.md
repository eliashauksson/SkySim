# SkySim

**SkySim** is a **prototype for a weather/drone simulation** using OpenGL, GLFW, and GLAD, written in C++20.
It provides a basic framework for rendering, window management, and future logic for drones and environmental effects

> **Note:** This project has only been tested on Linux.

## Features

- Simple window management via a `Window` class
- Cross-platform-read (Windows/macOS support is not tested)
- CMake + Makefile build system

## Current Status

- The project has just been started.
- Window creation and OpenGL context initialization are set up, but **the simulation logic is not yet implemented**.

## Prerequisites

- C++20 compatible compiler
- CMake 3.20 or higher
- GLFW
- OpenGL development libraries

## Build and Run

Build the project

```bash
make
```

Run the application

```bash
make run 
```

Clean build artifacts

```bash
make clean
```