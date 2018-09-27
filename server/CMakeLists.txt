cmake_minimum_required(VERSION 3.7)
project(server)


message(STATUS "MAIN SERVER COMPILE_ROOT_PATH " ${COMPILE_ROOT_PATH})
message(STATUS "start prepare main server..........")

include_directories(${COMPILE_ROOT_PATH}/server/src)

aux_source_directory(src SERVER_SOURCES)

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -GGDB -Wall -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -w")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DTRACE_LOG -DNDEBUG)
else()
    add_definitions(-D_DEBUG -DTRACE_LOG -D__SERVER)
endif()

link_directories(${STATIC_LIB_OUTPUT_PATH} ${SHARED_LIB_OUTPUT_PATH})
add_executable(server ${SERVER_SOURCES})
target_link_libraries(server -lnett -lcommon -lthread -ldl netserialize protobuf)

file(COPY ${COMPILE_ROOT_PATH}/start.sh DESTINATION ${EXEC_OUTPUT_PATH})
file(COPY ${COMPILE_ROOT_PATH}/stop.sh DESTINATION ${EXEC_OUTPUT_PATH})
file(COPY ${COMPILE_ROOT_PATH}/show.sh DESTINATION ${EXEC_OUTPUT_PATH})
file(COPY ${COMPILE_ROOT_PATH}/config/ DESTINATION ${EXEC_OUTPUT_PATH}/config)
#是否可以带上版本号
install(TARGETS server DESTINATION ${EXEC_OUTPUT_PATH})