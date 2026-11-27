cmake_minimum_required(VERSION 3.20)
project(mc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(mc src/main.cpp src/Shader.cpp src/Camera.cpp)
target_compile_definitions(mc PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/src/")
target_link_libraries(mc PRIVATE glfw GLEW::GLEW glm::glm OpenGL::GL)
target_compile_options(mc PRIVATE -Wall -Wextra)