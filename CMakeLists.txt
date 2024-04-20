cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(flightComputer)

pico_sdk_init()

add_executable(${PROJECT_NAME} src/main.cpp)
target_sources(${PROJECT_NAME}
  PRIVATE
    src/ICM46288.cpp
    src/I2CUtils.cpp
)

add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
  pico_stdlib
  hardware_i2c
  FatFs_SPI
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
