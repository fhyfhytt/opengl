cmake_minimum_required(VERSION 3.14)
project(glfw)
include_directories(include)
link_directories(lib)
set(CMAKE_C_STANDARD 99)
add_executable(glfw main.cpp image.cpp glad.c)

target_link_libraries(glfw libglfw3.a)