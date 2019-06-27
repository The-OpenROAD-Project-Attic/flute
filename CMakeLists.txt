cmake_minimum_required (VERSION 3.9)
project(Flute VERSION 3.3)

set(FLUTE_HOME ${PROJECT_SOURCE_DIR})

message(STATUS "Flute version: ${PROJECT_VERSION}")

# Default to bulding optimnized/release executable.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif()

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build CXX_FLAGS: ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
message(STATUS "CXX_FLAGS: ${COMPILE_OPTIONS}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

add_library(flute ${FLUTE_HOME}/flute.cpp)

target_include_directories(flute PUBLIC ${FLUTE_HOME})

target_compile_options(flute PUBLIC -std=c++11)

add_executable(rand-pts ${FLUTE_HOME}/rand-pts.c)

add_executable(flute-net ${FLUTE_HOME}/flute-net.cpp)

target_link_libraries(flute-net flute)
