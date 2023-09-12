cmake_minimum_required(VERSION 3.12)

get_filename_component(PARENT_DIR ../../ ABSOLUTE)

include(${PARENT_DIR}/pico_sdk_import.cmake)
# include(pico_extras_import_optional.cmake)

project(tentacle_controller C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(main main.c)

# pull in common dependencies
target_link_libraries(main pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(main)

# add url via pico_set_program_url
# example_auto_set_url(main)
