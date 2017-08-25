cmake_minimum_required(VERSION 3.7)
project(test_common)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "COMMON TEST COMPILE_ROOT_PATH " ${COMPILE_ROOT_PATH})

add_subdirectory(test_config)
add_subdirectory(test_log_trace)