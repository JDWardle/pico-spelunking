add_executable(breadboard_hello breadboard_hello.c)

target_link_libraries(breadboard_hello pico_stdlib)

pico_add_extra_outputs(breadboard_hello)
