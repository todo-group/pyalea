cmake_minimum_required(VERSION 3.14...3.22)
include(cmake/prefix.cmake)
project(pyalea CXX)
include(cmake/postfix.cmake)

include(pybind11)
FetchContent_MakeAvailable(${FetchContents})
include_directories(${FetchContent_includes})

find_package(ALPSCore REQUIRED)

add_subdirectory(src)
add_subdirectory(example)
