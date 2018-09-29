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
    set(EXEC_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/release)
    set(SHARED_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/release)
    set(STATIC_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/lib/release)
else()
    set(EXEC_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/debug)
    set(SHARED_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/bin/debug)
    set(STATIC_LIB_OUTPUT_PATH ${COMPILE_ROOT_PATH}/lib/debug)
endif()

if(COMPILE_TOOL STREQUAL "command")
    message("command model")
else()
    set(EXECUTABLE_OUTPUT_PATH ${EXEC_OUTPUT_PATH})
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SHARED_LIB_OUTPUT_PATH})
    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${STATIC_LIB_OUTPUT_PATH})
endif()

message("SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
message("COMPILE_TYPE = ${COMPILE_TYPE}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")
message("EXEC_OUTPUT_PATH = ${EXEC_OUTPUT_PATH}")
message("STATIC_LIB_OUTPUT_PATH = ${STATIC_LIB_OUTPUT_PATH}")
message("SHARED_LIB_OUTPUT_PATH = ${SHARED_LIB_OUTPUT_PATH}")
message("CMAKE_LIBRARY_PATH = ${CMAKE_LIBRARY_PATH}")
message("COMPILE_TOOL = ${COMPILE_TOOL}")
message("EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")


include_directories(/usr/local/include)
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/package/protobuf/hpb)
include_directories(${PROJECT_SOURCE_DIR}/third_party)
include_directories(${PROJECT_SOURCE_DIR}/third_party/protobuf-2.6.0)

#third_party
add_subdirectory(third_party)
#common
add_subdirectory(common)
#pb_serialize
add_subdirectory(pb_serialize)
#network
add_subdirectory(network/nett)
#server
add_subdirectory(server)
#test
add_subdirectory(test)