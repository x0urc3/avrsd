add_library(avrunit INTERFACE)
target_include_directories(avrunit INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(spi)
add_subdirectory(sd)
