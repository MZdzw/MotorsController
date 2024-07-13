cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS_DEBUG   "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3")

set(CXX_WARNINGS "-Wall -Wextra")

find_package(GTest REQUIRED)

set(TEST_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/Test_MovementElementTask.cpp)
set(PROD_INCS    ${CMAKE_SOURCE_DIR}/Src/Tasks
                 ${CMAKE_SOURCE_DIR}/Src/HalWrapper
                 ${CMAKE_SOURCE_DIR}/Src/MovementElement
                 ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver)
set(PROD_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/gen/genMovementElementTask.cpp
                 ${CMAKE_SOURCE_DIR}/Src/MovementElement/MovementElement.cpp
                 ${CMAKE_SOURCE_DIR}/Src/StepperMotorDriver/StepperMotorDriver.cpp)
set(MOCK_INCS    ${CMAKE_SOURCE_DIR}/Tests)

# FreeRTOS is located out of tree. Need to explicitly indicate binary location
add_subdirectory(${CMAKE_SOURCE_DIR}/Src/FreeRTOS ${CMAKE_BINARY_DIR}/Src/FreeRTOS)

add_executable(Test_MovementElementTask ${PROD_SRCS} ${TEST_SRCS})

target_compile_definitions(Test_MovementElementTask PRIVATE TESTING=1 TESTING_FREERTOS=1)
target_include_directories(Test_MovementElementTask PRIVATE ${PROD_INCS} ${MOCK_INCS})


# Add libraries
target_link_directories(Test_MovementElementTask PRIVATE ${CMAKE_BINARY_DIR}/Src/FreeRTOS)
target_link_libraries(Test_MovementElementTask PRIVATE
                      GTest::gmock
                      GTest::gtest_main
                      FreeRTOS)

