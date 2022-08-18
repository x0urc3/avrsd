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

#define SD_CMD_PREAMBLE     0x40
#define SD_CMD_POSTAMBLE    0x01

#define CMD0            0
#define CMD0_CRC        0x94    // valid for argument 0x0

#define CMD8            8
#define VHS_27_36       0x1
#define CHECK_PATTERN   0xAA
#define CMD8_ARG        (VHS_27_36 << 8) | CHECK_PATTERN
#define CMD8_CRC        0x86    // valid for argument 0x1AA

#define CMD55           55
#define ACMD41          41
#define ACMD41_ARG1     0X40000000    // HSC=1 (1<<30), Ver2 SDHC/SDXC
#define ACMD41_ARG0     0             // HSC=0, Ver1 or Ver2 SD Standard Capacity

#define CMD13           13
#define CMD17           17

#define R1_OK               0
#define R1_IDLE_STATE       (1<<0)
#define R1_ILLEGAL_COMMAND  (1<<1)

#define TOKEN_SINGLE_BLOCK_START    0xFE

enum error {
    CMD0_ERROR,
    CMD8_ERROR,
    ACMD41_ERROR
};

void SD_setup(void);
void SD_powerUp(void);
void SD_writeCmd(uint8_t codeword, uint32_t arg, uint8_t crc);
uint8_t SD_readR1(void);
void SD_readResponse(uint8_t *res, const uint8_t size);
uint8_t SD_init(void);

#define SD_writeAcmd(codeword, arg, crc)    \
    SD_writeCmd(CMD55, 0, 0);   \
    SD_readR1();   \
    SD_writeCmd(codeword, arg, crc);

#endif // _SD_H
