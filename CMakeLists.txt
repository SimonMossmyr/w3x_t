cmake_minimum_required(VERSION 3.10)

project(w3x_t VERSION 0.0.0)

set(LIB_FILES
    lib/utils.cc
    lib/w3e.cc
    lib/shd.cc
    lib/wpm.cc
    lib/doo.cc
    lib/units_doo.cc
    lib/w3i.cc
    lib/wts.cc
    lib/mmp.cc
    lib/w3o.cc
    lib/wtg.cc
    lib/trigger_data.cc
    lib/w3c.cc
    lib/w3r.cc
    lib/w3s.cc
    lib/wct.cc
    lib/imp.cc
)

set(SRC_FILES
    src/utils.cc
)

add_executable(w3x_t src/main.cc "${SRC_FILES}" "${LIB_FILES}")
target_compile_options(w3x_t PRIVATE -Wall -pedantic -Og)
target_include_directories(w3x_t PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(w3x_t
    storm
    casc
    z
    bz2
    stdc++fs
)
