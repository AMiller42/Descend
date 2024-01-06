cmake_minimum_required(VERSION 3.16) # Oldest tested version
set(CMAKE_CXX_STANDARD 20)

project(Descend VERSION 0.0)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(Descend)
target_sources(Descend PRIVATE "${SRC_DIR}/descend.cpp")
target_sources(Descend PRIVATE "${SRC_DIR}/lexer.cpp")
target_sources(Descend PRIVATE "${SRC_DIR}/token.cpp")
