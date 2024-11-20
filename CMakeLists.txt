cmake_minimum_required(VERSION 3.15...3.30)
include(cmake/prefix.cmake)
project(pyalea CXX)
include(cmake/postfix.cmake)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
include(pybind11)
FetchContent_MakeAvailable(${FetchContents})

find_package(MPI REQUIRED)
find_package(HDF5 REQUIRED)
find_package(ALPSCore REQUIRED)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(test)
  add_subdirectory(example)
endif()
