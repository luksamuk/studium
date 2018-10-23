cmake_minimum_required(VERSION 2.8)

project(studium)
set(CMAKE_C_STANDARD 11)

file(GLOB studium_SRC
  "src/*.c")

# set(CMAKE_BUILD_TYPE RelWithDebugInfo)
set(CMAKE_BUILD_TYPE Debug)

# Static GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.2.1)
include_directories(glfw-3.2.1/include)

## Build configuration

# GLAD GL loader
add_library(glad STATIC
  src/glad.c)

# libstudium
add_library(studium SHARED ${studium_SRC})
target_link_libraries(studium glad glfw)


## Instalation configuration
# libstudium library
install(TARGETS studium
  LIBRARY DESTINATION lib)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/studium
  DESTINATION include
  FILES_MATCHING PATTERN "*.h")

## Extra stuff
include_directories(src/)

# Test binary
add_executable(studium-test
  test/studium-test.c)

# Unit tests
add_executable(unit-tests
  test/tests.c)

target_link_libraries(studium-test studium)

target_link_libraries(unit-tests studium check)

enable_testing()
add_test(NAME unit-tests
  COMMAND ${CMAKE_BINARY_DIR}/unit-tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
