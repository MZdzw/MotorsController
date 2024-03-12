cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CXX_WARNINGS "-Wall -Wextra")

find_package(GTest REQUIRED)

set(TEST_SRCS StepperMotorDriver/test_StepperMotorDriver.cpp)
set(PROD_INCS ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver)
set(PROD_SRCS ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver/stepperMotorDriver.cpp)

add_executable(Tests ${TEST_SRCS} ${PROD_SRCS})

target_include_directories(Tests PRIVATE ${PROD_INCS})

target_link_libraries(Tests PRIVATE
   GTest::gtest_main)

add_test(NAME tests COMMAND Tests)

