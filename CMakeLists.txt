cmake_minimum_required(VERSION 3.13)

include(pico-sdk/pico_sdk_init.cmake)

project(pico C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

add_subdirectory(blink)
add_subdirectory(breadboard_hello)
add_subdirectory(button)
add_subdirectory(lcd_1602_i2c)
add_subdirectory(lib)
add_subdirectory(humidity)
