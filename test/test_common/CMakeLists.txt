cmake_minimum_required(VERSION 3.7)
project(test_common)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "COMMON TEST COMPILE_ROOT_PATH " ${COMPILE_ROOT_PATH})

add_subdirectory(test_aes)
add_subdirectory(test_config)
add_subdirectory(test_base_fun)
add_subdirectory(test_base_queue)
add_subdirectory(test_thread)
add_subdirectory(test_cache_map)
add_subdirectory(test_lock)
add_subdirectory(test_log_trace)
add_subdirectory(test_mem_cache)
add_subdirectory(test_mem_codec)
add_subdirectory(test_sensitive)
add_subdirectory(test_system)