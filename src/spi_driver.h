#ifndef _SPI_H
#define _SPI_H
#include <avr/io.h>

#define SPI_DDR             DDRB
#define SPI_PORT            PORTB
#define SPI_PIN_CS          PINB2
#define SPI_PIN_MOSI        PINB3
#define SPI_PIN_MISO        PINB4
#define SPI_PIN_SCK         PINB5

#define SPI_CS_ENABLE()     SPI_PORT &= ~_BV(SPI_PIN_CS)
#define SPI_CS_DISABLE()    SPI_PORT |= _BV(SPI_PIN_CS)

void SPI_init(void);
uint8_t SPI_rw(uint8_t data);

#endif // _SPI_H
