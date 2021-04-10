add_executable(lcd_1602_i2c lcd_1602_i2c.c)

target_link_libraries(lcd_1602_i2c pico_stdlib hardware_i2c)

pico_add_extra_outputs(lcd_1602_i2c)
