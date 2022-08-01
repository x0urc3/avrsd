add_library(spi STATIC spi.c)
setup_avr_target(spi)
target_include_directories(spi PUBLIC
    "$<BUILD_INTERFACE:$<$<BOOL:$<TARGET_PROPERTY:SPI_PRIVATE>>:${CMAKE_SOURCE_DIR}>>")
set_target_properties(spi PROPERTIES SPI_PRIVATE 1)


