cmake_minimum_required(VERSION 3.3)

project("satcaster")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${SRC_DIR}/EasyBMP)

add_definitions(
  -std=c++11
)

add_executable(
  satcaster main.cpp
            Vec3.cpp
            Satcaster.cpp
)
