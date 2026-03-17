cmake_minimum_required(VERSION 3.14)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source build is not allowed. Please use out-of-source build: mkdir build && cd build && cmake ..")
endif()

project(clibus)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLIBUS_EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    if(EXISTS ${CLIBUS_EXTERNAL_DIR}/googletest-1.17.0)
        add_subdirectory(${CLIBUS_EXTERNAL_DIR}/googletest-1.17.0 ${CMAKE_BINARY_DIR}/googletest)
        set(GTest_FOUND TRUE)
    else()
        message(WARNING "GTest not found, tests will be skipped. Install via: brew install googletest")
    endif()
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

if(EXISTS ${CLIBUS_EXTERNAL_DIR}/cpp-httplib-0.38.0)
    include_directories(${CLIBUS_EXTERNAL_DIR}/cpp-httplib-0.38.0)
else()
    message(FATAL_ERROR "cpp-httplib not found in external/cpp-httplib-0.38.0")
endif()

if(EXISTS ${CLIBUS_EXTERNAL_DIR}/googletest-1.17.0/googletest/include)
    include_directories(${CLIBUS_EXTERNAL_DIR}/googletest-1.17.0/googletest/include)
    include_directories(${CLIBUS_EXTERNAL_DIR}/googletest-1.17.0/googlemock/include)
endif()

add_library(clibus_core src/clibus.cpp)

add_executable(clibus src/main.cpp)
target_link_libraries(clibus clibus_core)

if(GTest_FOUND)
    enable_testing()
    
    add_executable(clibus_test test/clibus_test.cpp)
    target_link_libraries(clibus_test clibus_core gmock_main gtest_main)

    add_executable(fetchurl_test test/fetchurl_test.cpp)
    target_link_libraries(fetchurl_test clibus_core gmock_main gtest_main)

    include(GoogleTest)
    gtest_discover_tests(clibus_test)
    gtest_discover_tests(fetchurl_test)
endif()
