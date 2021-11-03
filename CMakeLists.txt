cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(stewie C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(RASPBERRY_PICO)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    pico/portable.c
    main.c
    display.c
    flippers.c
    game.c
    lamps.c
    sounds.c
    mcp23017.c
    is31fl3731.c
    stewie-lamps.c
    switches.c
)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_pwm
    hardware_i2c
)

# switch to USB CDC (USB serial)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
