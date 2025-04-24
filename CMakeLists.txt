cmake_minimum_required( VERSION 3.30.1)
project( BigReal )

set( CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set( CMAKE_DISABLE_SOURCE_CHANGES ON)

set( CMAKE_BUILD_TYPE Debug)
set( CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_STANDARD_REQUIRED ON)
set( CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

set( INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

file (GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

include( FetchContent)
FetchCOntent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set( gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
add_executable(Conversion  tests/conv.cpp ${SOURCES})
add_executable(ArithmTest  tests/arithm.cpp ${SOURCES})
add_executable(Bool_oper tests/Bool_oper.cpp ${SOURCES})

target_link_libraries(
    ArithmTest
    GTest::gtest_main
)

target_link_libraries(
    Conversion
    GTest::gtest_main
)

target_link_libraries(
    Bool_oper
    GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(Conversion)
gtest_discover_tests(ArithmTest)
gtest_discover_tests(Bool_oper)