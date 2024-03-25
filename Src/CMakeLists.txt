cmake_minimum_required(VERSION 3.22)
message("Build Type ") # Wyświetlenie listy nazw bibliotek

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CORE_FLAGS "-mcpu=cortex-m3 -mthumb")
set(CORE_FLAGS "${CORE_FLAGS}")
set(CXX_FLAGS "-fno-rtti -fno-exceptions -fverbose-asm -MMD")
set(C_FLAGS "-ffunction-sections -fdata-sections -fstack-usage -MMD -MP")
set(ASM_FLAGS "-x assembler-with-cpp")
set(CXX_WARNINGS "-Wall -Wextra")
set(C_WARNINGS "-Wall -Wextra")
set(CMAKE_LINKER "/usr/bin/arm-none-eabi-g++")
set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${C_FLAGS} ${C_WARNINGS}")
set(CMAKE_ASM_FLAGS "${ASM_FLAGS} ${CORE_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_CXX_FLAGS_DEBUG   "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3")
set(CMAKE_C_FLAGS_DEBUG   "-g3 -O0")
set(CMAKE_C_FLAGS_RELEASE "-g0 -O3")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs -Wl,-Map=\
\"${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map\" -Wl,--gc-sections -static --specs=nano.specs \
-Wl,--start-group -lc -lm -Wl,--end-group -Wl,--print-memory-usage")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Src/StartupLinkerScript/STM32F103RBTx_FLASH.ld)
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
set(SYMBOLS
    -DSTM32
    -DSTM32F1
    -DSTM32F103xB
    -DUSE_HAL_DRIVER)

set(INCLUDES       ${CMAKE_CURRENT_SOURCE_DIR}/Periph
                   ${CMAKE_CURRENT_SOURCE_DIR}/SystemHal
                   ${CMAKE_CURRENT_SOURCE_DIR}/StepperMotorDriver
                   ${CMAKE_CURRENT_SOURCE_DIR}/HalWrapper
                   ${CMAKE_CURRENT_SOURCE_DIR}/MovementElement)
set(PERIPH_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/Periph/gpio.c
                   ${CMAKE_CURRENT_SOURCE_DIR}/Periph/usart.c)
set(SYS_HAL_SRCS   ${CMAKE_CURRENT_SOURCE_DIR}/SystemHal/stm32f1xx_hal_msp.c
                   ${CMAKE_CURRENT_SOURCE_DIR}/SystemHal/stm32f1xx_it.c
                   ${CMAKE_CURRENT_SOURCE_DIR}/SystemHal/system_stm32f1xx.c)
set(STARTUP_FILE   ${CMAKE_CURRENT_SOURCE_DIR}/StartupLinkerScript/startup_stm32f103xb.s)
set(STPMOT_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/StepperMotorDriver/stepperMotorDriver.cpp)
set(HAL_WRPS       ${CMAKE_CURRENT_SOURCE_DIR}/HalWrapper/HalWrapper.cpp)
set(MOVELEM_SRCS   ${CMAKE_CURRENT_SOURCE_DIR}/MovementElement/MovementElement.cpp)

add_subdirectory(CMSIS_HAL)
add_subdirectory(FreeRTOS)

add_executable(${EXECUTABLE} main.cpp ${PERIPH_SRCS} ${SYS_HAL_SRCS} ${STARTUP_FILE}
               ${STPMOT_SRCS} ${HAL_WRPS} ${MOVELEM_SRCS})

# Add libraries
target_link_directories(${EXECUTABLE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS_HAL/CMSIS/Lib/GCC
                                              ${CMAKE_BINARY_DIR}/Src/CMSIS_HAL
                                              ${CMAKE_BINARY_DIR}/Src/FreeRTOS)
target_link_libraries(${EXECUTABLE} PRIVATE -larm_cortexM3l_math CMSIS_HAL FreeRTOS)

# Include paths
target_include_directories(${EXECUTABLE} PRIVATE ${INCLUDES})

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE ${SYMBOLS})

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
    -T${LINKER_SCRIPT}
)

# Execute post-build to print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)

