cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(TemplateProject)

pico_sdk_init()
set(PICO_BOARD pico_w)

add_executable(main main.c)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

pico_add_extra_outputs(main)

target_link_libraries(main pico_stdlib hardware_i2c)

#target_link_libraries(main pico_cyw43_arch_none)

