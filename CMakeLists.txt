# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
#set(PICO_SDK_PATH "/home/shiyou/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico-sdk/pico_sdk_init.cmake)

project(PicoDX C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(PicoDX pico-sdk/src/rp2_common/pico_multicore/include/pico/multicore.h src/PicoDX.cpp src/usb_descriptors.c src/picodx_hid.cpp src/ControlHandler.cpp libs/pio_rotary_encoder.cpp src/FileManager.cpp libs/lfs/littlefs-lib/pico_hal.c libs/lfs/littlefs-lib/lfs.c) 
# Make sure TinyUSB can find tusb_config.h
target_include_directories(PicoDX PUBLIC
        ${CMAKE_CURRENT_LIST_DIR} src libs libs/lfs/littlefs-lib pico-sdk/src/rp2_common/pico_multicore/include/pico)

pico_generate_pio_header(PicoDX ${CMAKE_CURRENT_LIST_DIR}/libs/pio_rotary_encoder.pio)

pico_set_program_name(PicoDX "PicoDX")
pico_set_program_version(PicoDX "0.1")

pico_enable_stdio_uart(PicoDX 0)
pico_enable_stdio_usb(PicoDX 0)



# Add the standard library to the build
target_link_libraries(PicoDX pico_stdlib hardware_pio tinyusb_device tinyusb_board hardware_flash pico_multicore)

pico_add_extra_outputs(PicoDX)

