cmake_minimum_required(VERSION 3.7)
project(nett)

message(STATUS "start prepare nett project......")

aux_source_directory(src NETT_SOURCES)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -ggdb -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -w")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DTRACE_LOG -DNDEBUG -D__SERVER -DAPI_EXPORTS)
else()
    add_definitions(-D_DEBUG -DTRACE_LOG -D__SERVER -DAPI_EXPORTS)
endif()

link_directories(${SHARED_LIB_OUTPUT_PATH})
add_library(nett SHARED ${NETT_SOURCES})
target_link_libraries(nett -lcommon)

install(TARGETS nett DESTINATION ${SHARED_LIB_OUTPUT_PATH})