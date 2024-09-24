cmake_minimum_required(VERSION 3.30.3)

project(Glad)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
