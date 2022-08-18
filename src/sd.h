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
#define ACMD41_ARG_HCS1 0X40000000    // HSC=1 (1<<30), Ver2 SDHC/SDXC
#define ACMD41_ARG_HCS0 0             // HSC=0, Ver1 or Ver2 SD Standard Capacity

#define CMD13           13
#define CMD17           17
#define CMD24           24

#define SD_MAX_READ_CYCLE   1562    // Maximum length of 100ms
                                    // 100ms * (16Mhz / 128) / 8bit
#define SD_MAX_WRITE_CYCLE  3906    // Maximum length of 250ms
                                    // 250ms * (16Mhz / 128) / 8bit

#define R1_OK               0
#define R1_IDLE_STATE       (1<<0)
#define R1_ILLEGAL_COMMAND  (1<<1)

#define TOKEN_BLOCK_START               0xFE
#define TOKEN_READ_ERROR                0x1
#define TOKEN_READ_ERROR_CC             0x2
#define TOKEN_READ_ERROR_ECC            0x4
#define TOKEN_READ_ERROR_OUT_OF_RANGE   0x8
#define TOKEN_WRITE_MASK                0x1f // 0b00011111
#define TOKEN_WRITE_ACCEPT              0x5 // 0bxxx00101
#define TOKEN_WRITE_ERROR_CRC           0xb // 0bxxx01011
#define TOKEN_WRITE_ERROR               0xd // 0bxxx01101

#define SD_BLOCK_LENGTH 512

enum status {
    SUCCESS,
    CMD0_ERROR,
    CMD8_ERROR,
    ACMD41_ERROR,
    CMD17_ERROR,
    CMD17_READ_ERROR,
    CMD24_ERROR,
    CMD24_WRITE_ERROR
};

void SD_setup(void);
void SD_powerUp(void);
void SD_writeCmd(uint8_t codeword, uint32_t arg, uint8_t crc);
uint8_t SD_readR1(void);
void SD_readResponse(uint8_t *res, const uint8_t size);
uint8_t SD_init(void);
uint8_t SD_writeBlock(const uint8_t *dat, uint32_t addr);
uint8_t SD_readBlock(uint8_t *dat, uint32_t addr);

#define SD_writeAcmd(codeword, arg, crc)    \
    SD_writeCmd(CMD55, 0, 0);   \
    SD_readR1();   \
    SD_writeCmd(codeword, arg, crc);

#endif // _SD_H
