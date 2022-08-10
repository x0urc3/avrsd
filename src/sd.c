#include <util/delay.h>
#include "spi_driver.h"
#include "sd.h"

void SD_init(void) {
    SPI_init();

#ifdef SD_PIN_VCC
    SD_DDR |= _BV(SD_PIN_VCC);
#endif // SD_PIN_VCC
}

/*
 * SD power up sequence
 * - CS held high i.e. CS disable
 * - Provide at least 1ms and 74 clock cycles while keeping CMD line to high
 */
void SD_powerUp(void) {

#ifdef SD_PIN_VCC
    SD_ENABLE();
#endif // SD_PIN_VCC

    SPI_CS_DISABLE();
    _delay_ms(1);

    for (uint8_t i = 0; i < 10; i++)
        SPI_rw(0xff);

    SPI_CS_DISABLE();
}
