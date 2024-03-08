cmake_minimum_required(VERSION 3.22)

set(CORE_FLAGS "-mcpu=cortex-m3 -mthumb -DUSE_HAL_DRIVER -DSTM32F103xB")
set(CORE_FLAGS "${CORE_FLAGS} -g3")
set(CXX_FLAGS "-std=gnu++17 -O0 -g -fno-rtti -fno-exceptions -fverbose-asm -MMD")
set(C_FLAGS "-O3 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP")
set(CXX_WARNINGS "-Wall -Wextra")
set(C_WARNINGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${C_FLAGS} ${C_WARNINGS}")

set(FREERTOS_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/GCC/ARM_CM3/
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/include/)

set(FREERTOS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/timers.c

    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/GCC/ARM_CM3/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/MemMang/heap_4.c)

add_library(FreeRTOS STATIC ${FREERTOS_SRCS})

target_include_directories(FreeRTOS PUBLIC ${FREERTOS_INC})


