cmake_minimum_required(VERSION 2.8)

project(studium)

file(GLOB studium_SRC
  "src/*.c")

set(CMAKE_BUILD_TYPE Debug)

# Static GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.2.1)
include_directories(glfw-3.2.1/include)

# GLAD GL loader
add_library(glad STATIC
  src/glad.c)

# libstudium
add_library(studium SHARED ${studium_SRC})

# Test binary
add_executable(studium-test
  src/main.c)

target_link_libraries(studium-test
  studium
  glad
  glfw)
