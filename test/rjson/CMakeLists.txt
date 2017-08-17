cmake_minimum_required(VERSION 3.7)
project(rjson)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "JSON TEST COMPILE_ROOT_PATH " ${COMPILE_ROOT_PATH})
include_directories(${COMPILE_ROOT_PATH}/network/nett/src)

aux_source_directory(src JSONTEST_SOURCES)
LINK_DIRECTORIES(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})
add_executable(jsontest ${JSONTEST_SOURCES})
#target_link_libraries(jsontest common.a nett.so)

#TARGETS:可执行文件
#PROGRAMS:非目标文件的可执行程序(比如脚本)
#FILES
#DRECTORY
install(TARGETS jsontest DESTINATION ${EXECUTABLE_OUTPUT_PATH}/test)