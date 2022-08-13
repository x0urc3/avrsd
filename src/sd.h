#ifndef _SD_H
#define _SD_H
#include "spi_driver.h"

#define SD_PIN_VCC PINB1
#define SD_DDR     DDRB
#define SD_PORT    PORTB

#ifdef SD_PIN_VCC
#define SD_ENABLE()     (SD_PORT |= _BV(SD_PIN_VCC))
#define SD_DISABLE()    (SD_PORT &= ~_BV(SD_PIN_VCC))
#endif // SD_PIN_VCC

void SD_init(void);
void SD_powerUp(void);

#endif // _SD_H
