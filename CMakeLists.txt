cmake_minimum_required(VERSION 3.3)

project("satcaster")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_definitions(
  -std=c++11
)

add_executable(
  satcaster main.cpp
)

