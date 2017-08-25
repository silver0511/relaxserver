cmake_minimum_required(VERSION 3.7)
project(libnett)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++0x -O0 -g -ggdb -Wall -pthread -fPIC -rdynamic")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++0x -w -O3 -pthread -fPIC -rdynamic")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DTRACE_LOG -DNDEBUG)
else()
    add_definitions(-D_DEBUG -DTRACE_LOG)
endif()

aux_source_directory(src LIBNETT_SOURCES)

add_library(nett SHARED ${LIBNETT_SOURCES})

install(TARGETS nett DESTINATION ${SHARED_LIB_OUTPUT_PATH})