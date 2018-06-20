cmake_minimum_required(VERSION 3.7)
project(test)

set(CMAKE_CXX_STANDARD 11)

include_directories(${COMPILE_ROOT_PATH}/third_party/gtest-1.7.0/include)

#rjson
add_subdirectory(test_rjson)
#common
add_subdirectory(test_common)