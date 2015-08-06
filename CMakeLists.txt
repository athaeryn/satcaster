cmake_minimum_required(VERSION 3.3)

project("satocaster")

include_directories("/usr/local/include/eigen3/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_executable(
  satocaster  main.cpp
              Sphere.cpp
              Camera.cpp
)

