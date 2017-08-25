cmake_minimum_required(VERSION 3.7)
project(libcommon)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src LIBCOMMON_SOURCES)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb -Wall -fPIC")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -w -O3 -fPIC")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DTRACE_LOG -DNDEBUG -D_GLIBCXX_DEPRECATED)
else()
    add_definitions(-D_DEBUG -DTRACE_LOG -D__SERVER -D_GLIBCXX_DEPRECATED)
endif()

add_library(common STATIC ${LIBCOMMON_SOURCES})

install(TARGETS common DESTINATION ${STATIC_LIB_OUTPUT_PATH})


