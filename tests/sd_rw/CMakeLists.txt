add_executable(TEST_sd_rw test_sd_rw.c)
setup_avr_target(TEST_sd_rw)
target_link_libraries(TEST_sd_rw avrunit sd)

add_avr_test(TEST_sd_rw)
