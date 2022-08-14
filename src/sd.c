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

/*
 * Send SD command and return R1
 * - Hardcode CRC for CMD0
 */
#define SD_CMD_PREAMBLE 0x40
#define SD_CMD_POSTAMBLE 0x01
uint8_t SD_sendCmd(uint8_t codeword, uint32_t arg) {

    SPI_CS_ENABLE();

    SPI_rw(codeword|SD_CMD_PREAMBLE);
    SPI_rw((uint8_t)(arg >> 24));
    SPI_rw((uint8_t)(arg >> 16));
    SPI_rw((uint8_t)(arg >> 8));
    SPI_rw((uint8_t)(arg));
    uint8_t crc = 0;
    if (codeword == CMD0)
        crc = 0x94;
    if (codeword == CMD8)
        crc = 0x85;
    SPI_rw(crc|SD_CMD_POSTAMBLE);

    uint8_t r1, i = 0;
    do {
        r1 = SPI_rw(0xff) & 0x80;
        i++;
    } while ( r1 && i < 10);

    SPI_CS_DISABLE();

    return r1;
}
