cmake_minimum_required(VERSION 3.7)
project(test_thread)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "start prepare test_thread......")
include_directories(${COMPILE_ROOT_PATH}/include)

LINK_DIRECTORIES(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})

set(TEST_SOURCE test_thread.cpp)
add_executable(test_thread ${TEST_SOURCE})
target_link_libraries(test_thread -lpthread -ldl common.a)

#TARGETS:可执行文件
#PROGRAMS:非目标文件的可执行程序(比如脚本)
#FILES
#DIRECTORY
install(TARGETS test_thread DESTINATION ${EXEC_OUTPUT_PATH}/test/test_common/test_thread)