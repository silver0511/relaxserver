cmake_minimum_required(VERSION 3.7)
project(third_party)

add_subdirectory(gtest-1.7.0)
add_subdirectory(fakeit)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_TYPE linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM_TYPE mac)
else()
    message("Current System = ${CMAKE_SYSTEM_NAME} NOT ADAPTER")
endif()

#copy third_party
#file(COPY lib/${PLATFORM_TYPE}/libprotobuf.a DESTINATION ${STATIC_LIB_OUTPUT_PATH})