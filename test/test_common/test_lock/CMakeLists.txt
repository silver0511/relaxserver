cmake_minimum_required(VERSION 3.7)
project(test_lock)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "start prepare test_lock......")
include_directories(${COMPILE_ROOT_PATH}/include)

LINK_DIRECTORIES(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})

set(TEST_SOURCE test_lock.cpp)
add_executable(test_lock ${TEST_SOURCE})
target_link_libraries(test_lock -lpthread -ldl -lcommon)

#TARGETS:可执行文件
#PROGRAMS:非目标文件的可执行程序(比如脚本)
#FILES
#DIRECTORY
install(TARGETS test_lock DESTINATION ${EXEC_OUTPUT_PATH}/test/test_common/test_lock)