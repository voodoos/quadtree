cmake_minimum_required (VERSION 3.0)

project (test)

# Source files
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE source_list "${SRC}/*.cpp" "${SRC}/*.h")

add_executable(test ${source_list})
target_compile_features(test PRIVATE cxx_std_17)