add_executable(TEST_spi test_spi.c)
target_link_libraries(TEST_spi avrunit)
setup_avr_target(TEST_spi)

add_avr_test(TEST_spi)
