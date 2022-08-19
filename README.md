# rwSD

A minimal read/write SD card library using SPI mode.
SD Ver2 and AVR
single block read/write

## Feature
Timing use SPI clock cycle. Does not require
Unit test
Currently written for AVR microcontrollers see Porting Guide.

#Usage
- only provide read/write feature
- manage - buffer, number of blocks manually
- 512 bytes block size

## Configuration
- SPI speed
- wait cycle calculation

## Example

Example usage for 16Mhza ATmega328

```c
#include <avr/io.h>
#include "sd.h"

void main (void) {
    SD_setup();
    SD_init();

    uint8_t dat[SD_BLOCK_LENGTH];
    for (int i = 0; i < SD_BLOCK_LENGTH; i++) {
        dat[i] = 0xaa;
    }

    uint32_t addr = 0x11
    SD_writeBlock((const uint8_t *)dat, addr);
    SD_flush();

    uint8_t res[SD_BLOCK_LENGTH];
    uint8_t res[SD_BLOCK_LENGTH];
    SD_readBlock((uint8_t *)res, addr);

}
```

# Unit test

# Porting guide
spi_driver.c
