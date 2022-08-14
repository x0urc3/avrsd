/* rwSD Library
   Copyright (C) 2022 Khairulmizam Samsudin <xource@gmail.com

   This file is part of the rwSD Library

   This Library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the rwSD Library. If not, see
   <http://www.gnu.org/licenses/>.
*/
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
