# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
if (DEFINED ENV{PICO_SDK_PATH} AND (NOT PICO_SDK_PATH))
    set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    message("Using PICO_SDK_PATH from environment ('${PICO_SDK_PATH}')")
endif ()

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(tentacle-controller C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()



# Add executable. Default name is the project name, version 0.1

add_executable(tentacle-controller src/main.cpp )

target_sources(tentacle-controller PRIVATE 
  # src/util.cpp
  src/motor-driver/stepper-driver.cpp 
  src/motor-driver/timer-stepper-driver.cpp
  # src/motor-driver/pio-stepper-driver.cpp
  src/motor-driver/driver-configuration.cpp
  src/tentacle-controller.cpp
  )

  pico_generate_pio_header(tentacle-controller ${CMAKE_CURRENT_LIST_DIR}/src/motor-driver/stepper.pio)

pico_set_program_name(tentacle-controller "tentacle-controller")
pico_set_program_version(tentacle-controller "0.1")

pico_enable_stdio_uart(tentacle-controller 1)
pico_enable_stdio_usb(tentacle-controller 0)

# Add the standard library to the build
target_link_libraries(tentacle-controller pico_stdlib)

# Add the standard include files to the build
target_include_directories(tentacle-controller PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/src 
  ${CMAKE_CURRENT_LIST_DIR}/src/motor-driver
  # ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required

)

target_include_directories(tentacle-controller PUBLIC
  src

)

# Add any user requested libraries
target_link_libraries(tentacle-controller 
        hardware_i2c
        hardware_pio
        )

pico_add_extra_outputs(tentacle-controller)

