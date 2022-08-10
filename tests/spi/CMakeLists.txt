add_executable(TEST_spi test_spi.c)
setup_avr_target(TEST_spi)
target_link_libraries(TEST_spi avrunit spi)
set_target_properties(TEST_spi PROPERTIES SPI_PRIVATE 1)

add_avr_test(TEST_spi)
