cmake_minimum_required(VERSION 3.10)

project(w3x_t VERSION 0.0.0)

set(SRC_FILES
  src/utils.cc
  src/header.cc
  src/w3e.cc
  src/shd.cc
  src/wpm.cc
  src/doo.cc
  src/units_doo.cc
  src/w3i.cc
  src/wts.cc
)

add_executable(w3x_t
  src/main.cc
  "${SRC_FILES}"
)

target_include_directories(w3x_t PUBLIC
  "${PROJECT_BINARY_DIR}"
)

target_link_libraries(w3x_t
  storm
  z
  bz2
  stdc++fs
)
