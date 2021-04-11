add_library(i2c_lcd INTERFACE)

target_include_directories(i2c_lcd INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(i2c_lcd INTERFACE ${CMAKE_CURRENT_LIST_DIR}/lcd.c)
