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
#include "spi_driver.h"

void SPI_init(void) {
    SPI_DDR |= _BV(SPI_PIN_CS) | _BV(SPI_PIN_MOSI) | _BV(SPI_PIN_SCK);
    SPI_PORT |= _BV(SPI_PIN_MISO);

    // Enable SPI master and use leading edge sample
    SPCR = _BV(SPE) | _BV(MSTR);
    SPCR |= _BV(SPR1) | _BV(SPR0); // SCK frequency = fosc/128
}

uint8_t SPI_rw(uint8_t data) {
    SPDR = data;
    loop_until_bit_is_set(SPSR, SPIF);
    return SPDR;
}
