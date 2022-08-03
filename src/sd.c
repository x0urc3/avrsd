#include <util/delay.h>
#include "spi_driver.h"
#include "sd.h"

void SD_init(void) {
    SPI_init();
}

/*
 * SD power up sequence
 * - Provide at least 1ms and 74 clock cycles before sending command.
 */
void SD_powerUp(void) {
    SPI_CS_ENABLE();
    _delay_ms(1);

    for (uint8_t i = 0; i < 10; i++)
        SPI_rw(0xff);

    SPI_CS_DISABLE();
}
