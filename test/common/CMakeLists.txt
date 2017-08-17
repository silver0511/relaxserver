cmake_minimum_required(VERSION 3.7)
project(common)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "COMMON TEST COMPILE_ROOT_PATH " ${COMPILE_ROOT_PATH})
include_directories(${COMPILE_ROOT_PATH}/include)

LINK_DIRECTORIES(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})

set(CONFIG_TEST ./src/test_config.cpp)
add_executable(test_config ${CONFIG_TEST})
target_link_libraries(test_config common.a)

set(LOG_TRACE_TEST ./src/test_log_trace.cpp)
add_executable(test_log_trace ${LOG_TRACE_TEST})
target_link_libraries(test_log_trace common.a)

#TARGETS:可执行文件
#PROGRAMS:非目标文件的可执行程序(比如脚本)
#FILES
#DRECTORY
install(TARGETS test_config DESTINATION ${EXECUTABLE_OUTPUT_PATH}/test/common)