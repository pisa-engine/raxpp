cmake_minimum_required(VERSION 3.0)

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external) 

message(STATUS "ExternalProject_Add: rax")
configure_file(cmake/rax.cmake.in "${CMAKE_BINARY_DIR}/rax-download/CMakeLists.txt")
execute_process(COMMAND ${CMAKE_COMMAND} .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/rax-download)
if(result)
  message(FATAL_ERROR "CMake step for rax failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/rax-download)
execute_process(COMMAND cc -c -fPIC -std=c99 rax.c -o librax.a
                COMMAND mkdir -p ${EXTERNAL_INSTALL_LOCATION}
                COMMAND cp librax.a ${EXTERNAL_INSTALL_LOCATION}/librax.a
                COMMAND cp rax.h ${EXTERNAL_INSTALL_LOCATION}/rax.h
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/rax-src)
if(result)
  message(FATAL_ERROR "Build step for rax failed: ${result}")
endif()

message(STATUS "ExternalProject_Add: Catch2")
configure_file(cmake/catch2.cmake.in "${CMAKE_BINARY_DIR}/catch2-download/CMakeLists.txt")
execute_process(COMMAND ${CMAKE_COMMAND} .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch2-download)
if(result)
  message(FATAL_ERROR "CMake step for rax failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/catch2-download)
if(result)
  message(FATAL_ERROR "Build step for rax failed: ${result}")
endif()

list(APPEND CMAKE_MODULE_PATH ${EXTERNAL_INSTALL_LOCATION})
list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_INSTALL_LOCATION})
