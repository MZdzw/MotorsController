cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CXX_WARNINGS "-Wall -Wextra")

find_package(GTest REQUIRED)

set(TEST_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/StepperMotorDriver/test_StepperMotorDriver.cpp)
set(PROD_INCS    ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver
                 ${CMAKE_SOURCE_DIR}/Src/HalWrapper)
set(PROD_SRCS    ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver/stepperMotorDriver.cpp)
set(MOCK_INCS    ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Tests ${TEST_SRCS} ${PROD_SRCS})

target_compile_definitions(Tests PRIVATE TESTING=1)
target_include_directories(Tests PRIVATE ${PROD_INCS} ${MOCK_INCS})

target_link_libraries(Tests PRIVATE
   GTest::gtest_main)

add_test(NAME tests COMMAND Tests)

