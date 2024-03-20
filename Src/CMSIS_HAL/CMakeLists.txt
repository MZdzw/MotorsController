cmake_minimum_required(VERSION 3.22)

set(CORE_FLAGS "-mcpu=cortex-m3 -mthumb -DUSE_HAL_DRIVER -DSTM32F103xB")
set(CORE_FLAGS "${CORE_FLAGS} -g3")
set(CXX_FLAGS "-fno-rtti -fno-exceptions -fverbose-asm -MMD")
set(C_FLAGS "-ffunction-sections -fdata-sections -fstack-usage -MMD -MP")
set(CXX_WARNINGS "-Wall -Wextra")
set(C_WARNINGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${C_FLAGS} ${C_WARNINGS}")

set(CMSIS_INC ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32F1xx/Include
              ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include)
set(HAL_INC ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Inc
            ${CMAKE_SOURCE_DIR}/Src/SystemHal)
set(HAL_DRIVER_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c)

add_library(CMSIS_HAL STATIC ${HAL_DRIVER_SRCS})

target_include_directories(CMSIS_HAL PUBLIC ${CMSIS_INC} ${HAL_INC})

