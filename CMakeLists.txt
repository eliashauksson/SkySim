# CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(SkySim VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
file(GLOB SOURCES "src/*.cpp" "src/*.c")
add_executable(MyApp ${SOURCES})

# Include directories
target_include_directories(MyApp PRIVATE include include/glad include/KHR)

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(MyApp PRIVATE OpenGL::GL glfw)

# Copy shaders to build folder
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
