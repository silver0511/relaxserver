# Install script for directory: /Users/yunjie.shi/Documents/gitwork/relaxserver/test/test_common/test_thread

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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread/test_thread")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread" TYPE EXECUTABLE FILES "/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_thread/test_thread")
  if(EXISTS "$ENV{DESTDIR}/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread/test_thread" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread/test_thread")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/yunjie.shi/Documents/gitwork/relaxserver/lib/debug"
      "$ENV{DESTDIR}/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread/test_thread")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug"
      "$ENV{DESTDIR}/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread/test_thread")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/yunjie.shi/Documents/gitwork/relaxserver/bin/debug/test/test_common/test_thread/test_thread")
    endif()
  endif()
endif()

