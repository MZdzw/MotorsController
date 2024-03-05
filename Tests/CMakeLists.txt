cmake_minimum_required(VERSION 3.22)

find_package(GTest REQUIRED)

set(TEST_SRCS module_template/test_template.cpp)

add_executable(Tests ${TEST_SRCS})

target_link_libraries(Tests PRIVATE
   GTest::gtest_main)

add_test(NAME tests COMMAND Tests)

