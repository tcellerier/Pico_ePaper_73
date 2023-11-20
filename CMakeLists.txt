cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(Pico_ePaper_73)
pico_sdk_init()

# add a compilation subdirectory
add_subdirectory(lib/Config)
add_subdirectory(lib/e-Paper)
add_subdirectory(lib/RTC)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)
add_subdirectory(lib/led)
add_subdirectory(examples)
add_subdirectory(lib/FatFs_SPI build)

# add a header directory
include_directories(examples)
include_directories(./lib/Config)
include_directories(./lib/GUI)
include_directories(./lib/RTC)
include_directories(./lib/led)

# generate an executable file
add_executable(epd
main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(epd 1)
pico_enable_stdio_uart(epd 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(epd)

target_link_libraries(epd examples ePaper GUI led Fonts Config RTC FatFs_SPI)