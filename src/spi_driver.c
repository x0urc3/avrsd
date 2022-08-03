#include "spi_driver.h"

void SPI_init(void) {
    SPI_DDR |= _BV(SPI_PIN_CS) | _BV(SPI_PIN_MOSI) | _BV(SPI_PIN_SCK);
    SPI_PORT |= _BV(SPI_PIN_MISO);

    // Enable SPI master and use leading edge sample
    SPCR = _BV(SPE) | _BV(MSTR);
    SPCR |= _BV(SPR1) | _BV(SPR0); // SCK frequency = fosc/128
}
