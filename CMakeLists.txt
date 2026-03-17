cmake_minimum_required(VERSION 3.14)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source build is not allowed. Please use out-of-source build: mkdir build && cd build && cmake ..")
endif()

project(clibus)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.18.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest cpp-httplib)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${cpp-httplib_SOURCE_DIR})

add_library(clibus_core src/clibus.cpp)

add_executable(clibus src/main.cpp)
target_link_libraries(clibus clibus_core)

add_executable(clibus_test test/clibus_test.cpp)
target_link_libraries(clibus_test clibus_core gtest_main)

include(GoogleTest)
gtest_discover_tests(clibus_test)
