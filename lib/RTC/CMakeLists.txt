# Find all source files in a single current directory
# Save the name to DIR_ePaper_SRCS
aux_source_directory(. DIR_RTC_SRCS)

include_directories(../Config)

# Generate the link library
add_library(RTC ${DIR_RTC_SRCS})
target_link_libraries(RTC PUBLIC Config)