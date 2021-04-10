add_executable(button button.c)

target_link_libraries(button pico_stdlib)

pico_add_extra_outputs(button)
