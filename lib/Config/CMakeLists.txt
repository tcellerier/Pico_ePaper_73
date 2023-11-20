# Find all source files in a single current directory
# Save the name to DIR_Config_SRCS
aux_source_directory(. DIR_Config_SRCS)

# Generate the link library
add_library(Config ${DIR_Config_SRCS})
target_link_libraries(Config PUBLIC pico_stdlib hardware_spi hardware_adc hardware_i2c FatFs_SPI)