cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS_DEBUG   "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3")

set(CXX_WARNINGS "-Wall -Wextra")

find_package(GTest REQUIRED)

set(TEST_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/test_MovementElement.cpp)
set(PROD_INCS    ${CMAKE_SOURCE_DIR}/Src/MovementElement
                 ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver
                 ${CMAKE_SOURCE_DIR}/Src/HalWrapper)
set(PROD_SRCS    ${CMAKE_SOURCE_DIR}/Src/MovementElement/MovementElement.cpp)
set(MOCK_INCS    ${CMAKE_SOURCE_DIR}/Tests)

add_executable(Test_MovementElement ${PROD_SRCS} ${TEST_SRCS})

target_compile_definitions(Test_MovementElement PRIVATE TESTING=1)
target_include_directories(Test_MovementElement PRIVATE ${PROD_INCS} ${MOCK_INCS})

target_link_libraries(Test_MovementElement PRIVATE
                      gmock
                      GTest::gtest_main)

add_test(NAME tests COMMAND Test_MovementElement)
