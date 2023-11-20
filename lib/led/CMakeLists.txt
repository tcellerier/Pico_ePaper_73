# Find all source files in a single current directory
# Save the name to DIR_led_SRCS
aux_source_directory(. DIR_led_SRCS)

include_directories(../Config)

# Generate the link library
add_library(led ${DIR_led_SRCS})
target_link_libraries(led PUBLIC Config)