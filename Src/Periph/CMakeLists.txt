cmake_minimum_required(VERSION 3.22)

set(PERIPH_INC ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(PERIPH_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/usart.c)

set(CORE_FLAGS "-mcpu=cortex-m3 -mthumb -DUSE_HAL_DRIVER -DSTM32F103xB")
set(CORE_FLAGS "${CORE_FLAGS} -g3")
set(CXX_FLAGS "-std=gnu++17 -O0 -g -fno-rtti -fno-exceptions -fverbose-asm -MMD")
set(C_FLAGS "-O3 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP")
set(ASM_FLAGS "-x assembler-with-cpp")
set(CXX_WARNINGS "-Wall -Wextra")
set(C_WARNINGS "-Wall -Wextra")
set(LD_FLAGS " --specs=nosys.specs \
-Wl,-Map=\"${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map\" \
-Wl,--gc-sections -static -L\"${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Lib/GCC\" \
--specs=nano.specs -Wl,--start-group -lc -lm -Wl,--end-group -Wl,--print-memory-usage"
)
set(CMAKE_LINKER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_FLAGS "${CORE_FLAGS} ${CXX_FLAGS} ${CXX_WARNINGS}")
set(CMAKE_C_FLAGS "${CORE_FLAGS} ${C_FLAGS} ${C_WARNINGS}")
set(CMAKE_ASM_FLAGS "${ASM_FLAGS} ${CORE_FLAGS} ${CXX_WARNINGS}")
# Be careful to link things in proper order
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <OBJECTS> -o <TARGET> ${CORE_FLAGS} ${LD_FLAGS}")

add_library(Periph STATIC ${PERIPH_SRCS})

target_include_directories(Periph PUBLIC ${PERIPH_INC})

