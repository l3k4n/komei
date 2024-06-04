cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Komei VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

file(GLOB SOURCES src/main.cpp src/*/*.cpp)
add_executable(main ${SOURCES})

target_include_directories(main PUBLIC .)
