cmake_minimum_required(VERSION 3.16) # Oldest tested version
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

project(Descend VERSION 0.0)

add_executable(Descend)
target_sources(Descend PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/descend.cpp")

FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)
FetchContent_MakeAvailable(lexy)
target_link_libraries(Descend PRIVATE foonathan::lexy)
