#ifndef _SD_H
#define _SD_H
#include "spi_driver.h"

//#define SD_PIN_VCC PINB1

#ifdef SD_PIN_VCC
#define SD_DDR     DDRB
#define SD_PORT    PORTB

#define SD_ENABLE()     (SD_PORT |= _BV(SD_PIN_VCC))
#define SD_DISABLE()    (SD_PORT &= ~_BV(SD_PIN_VCC))
#endif // SD_PIN_VCC

#define CMD0    0
#define CMD8    8

void SD_init(void);
void SD_powerUp(void);
uint8_t SD_sendCmd(uint8_t codeword, uint32_t args);

#endif // _SD_H
