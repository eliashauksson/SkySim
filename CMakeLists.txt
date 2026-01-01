# CMakeLists.txt

# Cmake version
cmake_minimum_required(VERSION 3.20..4.21)

# Project statement
project(
    SkySim
    VERSION 0.1
    LANGUAGES C CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Exectuable
add_executable(MyApp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Window.cpp
)

# Includes
target_include_directories(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(MyApp PRIVATE glfw OpenGL::GL)
