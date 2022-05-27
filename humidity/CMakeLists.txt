add_executable(humidity humidity.c)

target_link_libraries(humidity pico_stdlib hardware_i2c i2c_lcd)

pico_add_extra_outputs(humidity)

pico_enable_stdio_usb(humidity 0)
pico_enable_stdio_uart(humidity 0)
