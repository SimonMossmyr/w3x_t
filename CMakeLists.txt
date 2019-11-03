# Clone StormLib and RapidJSON locally
# Then build and install the libraries
# 
# $ cd StormLib/build
# $ cmake ..
# $ make
# $ make install
# $ cd rapidjson/build
# $ cmake ..
# $ make
# $ make install
#
# This should make CMake find and link the two libraries

cmake_minimum_required(VERSION 3.10)

project(W3JSON VERSION 0.0.0)

set(SRC_FILES
  src/error.cc
  src/map_header.cc
  src/w3e.cc
)

add_executable(W3JSON
  src/main.cc
  "${SRC_FILES}"
)

target_include_directories(W3JSON PUBLIC
  "${PROJECT_BINARY_DIR}"
)

find_package(RapidJSON REQUIRED)
target_link_libraries(W3JSON
  storm
  z
  bz2
  stdc++fs
)
