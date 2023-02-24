cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/pico-sdk)
include(pico_sdk_import.cmake)

project(my_firmware C CXX ASM)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico-ice-sdk)

add_executable(my_firmware
    main.c
    usb_descriptors.c
)
target_link_libraries(my_firmware
    pico_ice_sdk
    pico_ice_usb
    pico_stdio_usb
)
target_include_directories(my_firmware PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
pico_enable_stdio_usb(my_firmware 1)
pico_add_extra_outputs(my_firmware)
