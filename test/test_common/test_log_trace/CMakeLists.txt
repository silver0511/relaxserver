cmake_minimum_required(VERSION 3.7)
project(test_log_trace)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "start prepare test_log_trace......")
include_directories(${COMPILE_ROOT_PATH}/include)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb -Wall -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -w -O3 -fPIC")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -w -O3 -fPIC -fshort-wchar -U__FILE__ -D__FILE__='\"$(subst $(dir $<),,$<)\"'")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DTRACE_LOG -DNDEBUG -D_GLIBCXX_DEPRECATED)
else()
    add_definitions(-D_DEBUG -DTRACE_LOG -D__SERVER -D_GLIBCXX_DEPRECATED)
endif()

LINK_DIRECTORIES(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})

set(TEST_SOURCE test_log_trace.cpp)
add_executable(test_log_trace ${TEST_SOURCE})
target_link_libraries(test_log_trace -lpthread -ldl -lcommon)

#TARGETS:可执行文件
#PROGRAMS:非目标文件的可执行程序(比如脚本)
#FILES
#DIRECTORY
install(TARGETS test_log_trace DESTINATION ${EXEC_OUTPUT_PATH}/test/test_common/test_log_trace)
install(PROGRAMS ./start.sh DESTINATION ${EXEC_OUTPUT_PATH}/test/test_common/test_log_trace)