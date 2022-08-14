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
