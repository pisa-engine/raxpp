cmake_minimum_required(VERSION 3.10)
project(raxpp VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${raxpp_SOURCE_DIR}/cmake)
include(CTest)

#
# CONFIGURATION
#
set(RAXPP_TARGET_NAME ${PROJECT_NAME})
set(RAXPP_CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(RAXPP_INCLUDE_INSTALL_DIR "include")
set(RAXPP_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(RAXPP_CMAKE_CONFIG_TEMPLATE "cmake/config.cmake.in")
set(RAXPP_CMAKE_CONFIG_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(RAXPP_CMAKE_VERSION_CONFIG_FILE
    "${RAXPP_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(RAXPP_CMAKE_PROJECT_CONFIG_FILE
    "${RAXPP_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(RAXPP_CMAKE_PROJECT_TARGETS_FILE
    "${RAXPP_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")

#
# OPTIONS
#
option(RAXPP_BUILD_TESTING "Enable testing" ON)
option(RAXPP_PULL_DEPS "Pull dependencies" ON)

if(RAXPP_PULL_DEPS)
    include(cmake/external.cmake)
endif()

#
# ADD LIBRARY
#
add_library(raxpp INTERFACE)
add_library(raxpp::raxpp ALIAS raxpp)
target_include_directories(
  raxpp
  INTERFACE $<BUILD_INTERFACE:${raxpp_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)

find_package(rax REQUIRED)
target_link_libraries(raxpp INTERFACE rax)

if (BUILD_TESTING AND RAXPP_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
