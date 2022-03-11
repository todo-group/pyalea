cmake_minimum_required(VERSION 3.14...3.22)
include(cmake/prefix.cmake)
project(pyalea CXX)
include(cmake/postfix.cmake)

include(pybind11)
FetchContent_MakeAvailable(${FetchContents})

find_package(MPI REQUIRED)
find_package(ALPSCore REQUIRED)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(example)
endif()
