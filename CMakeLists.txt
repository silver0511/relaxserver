cmake_minimum_required(VERSION 3.7)
project(relaxserver)

set(CMAKE_CXX_STANDARD 11)

#默认参数
#option(COMPILE_TYPE DEBUG)

if(COMPILE_TYPE STREQUAL "release")
    set(CMAKE_BUILD_TYPE Release)
else()
    set(CMAKE_BUILD_TYPE Debug)
endif()


set(COMPILE_ROOT_PATH ${PROJECT_SOURCE_DIR})
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    #set(EXECUTABLE_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/release)
    set(EXEC_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/release)
    set(SHARED_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/release)
    set(STATIC_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/lib/release)
else()
    #set(EXECUTABLE_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/debug)
    set(EXEC_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/debug)
    set(SHARED_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/debug)
    set(STATIC_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/lib/debug)
endif()

message("COMPILE_TYPE = ${COMPILE_TYPE}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
message("EXEC_OUTPUT_PATH = ${EXEC_OUTPUT_PATH}")
message("STATIC_LIB_OUTPUT_PATH = ${STATIC_LIB_OUTPUT_PATH}")
message("SHARED_LIB_OUTPUT_PATH = ${SHARED_LIB_OUTPUT_PATH}")


include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party)

#common
add_subdirectory(common)
#network
add_subdirectory(network/nett)
#third_party
add_subdirectory(third_party/gtest-1.7.0)
add_subdirectory(third_party/fakeit)
#test
add_subdirectory(test)