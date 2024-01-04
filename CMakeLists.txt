cmake_minimum_required(VERSION 3.16) # Oldest tested version
set(CMAKE_CXX_STANDARD 20)

project(Descend VERSION 0.0)

add_executable(Descend)
target_sources(Descend PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/descend.cpp")
target_sources(Descend PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.cpp")
