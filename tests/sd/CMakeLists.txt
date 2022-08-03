add_executable(TEST_sd test_sd.c)
setup_avr_target(TEST_sd)
target_link_libraries(TEST_sd avrunit sd)
set_target_properties(TEST_sd PROPERTIES SD_PRIVATE 1)

add_avr_test(TEST_sd)
