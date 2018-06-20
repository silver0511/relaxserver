# Install script for directory: /Users/yunjie.shi/Documents/gitwork/relaxserver/test/test_common

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_aes/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_config/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_fun/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_thread/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_cache_map/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_lock/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_log_trace/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_mem_cache/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_mem_codec/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_sensitive/cmake_install.cmake")
  include("/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_system/cmake_install.cmake")

endif()

