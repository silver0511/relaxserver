cmake_minimum_required(VERSION 3.7)
project(test_rjson)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "JSON TEST COMPILE_ROOT_PATH " ${COMPILE_ROOT_PATH})
message(STATUS "start prepare test_rjson......")
include_directories(${COMPILE_ROOT_PATH}/network/nett/src)

set(TEST_SOURCE test_rjson.cpp)
LINK_DIRECTORIES(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})
add_executable(test_rjson ${TEST_SOURCE})
#target_link_libraries(test_rjson -lpthread -ldl common.a nett.so)
target_link_libraries(test_rjson gtest gtest_main -lpthread -ldl common.a )

#TARGETS:可执行文件
#PROGRAMS:非目标文件的可执行程序(比如脚本)
#FILES
#DIRECTORY
install(TARGETS test_rjson DESTINATION ${EXEC_OUTPUT_PATH}/test/test_rjson)