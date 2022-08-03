add_library(spi STATIC spi_driver.c)
setup_avr_target(spi)
target_include_directories(spi PUBLIC
    "$<BUILD_INTERFACE:$<$<BOOL:$<TARGET_PROPERTY:SPI_PRIVATE>>:${CMAKE_CURRENT_SOURCE_DIR}>>")
set_target_properties(spi PROPERTIES SPI_PRIVATE 1)

add_library(sd STATIC sd.c)
setup_avr_target(sd)
target_include_directories(sd PUBLIC
    "$<BUILD_INTERFACE:$<$<BOOL:$<TARGET_PROPERTY:SD_PRIVATE>>:${CMAKE_CURRENT_SOURCE_DIR}>>")
set_target_properties(sd PROPERTIES SD_PRIVATE 1)
target_link_libraries(sd spi)
