cmake_minimum_required(VERSION 3.7)
project(pb_serialize)

aux_source_directory(hpb PB_SERIALIZE_SOURCES)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -ggdb -Wall -Wno-deprecated-declarations -Wno-sign-compare")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -w")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
else()
    add_definitions(-D_DEBUG)
endif()

add_library(pb_serialize STATIC ${PB_SERIALIZE_SOURCES})
target_link_libraries(pb_serialize protobuf)

install(TARGETS pb_serialize DESTINATION ${STATIC_LIB_OUTPUT_PATH})


