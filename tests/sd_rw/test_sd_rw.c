#include "avrunit.h"
#include "sd.h"

static int test_cmd17 (void) {
    AU_UNIT_START;

    SD_setup();
    SD_init();

    SPI_CS_ENABLE();
    SD_writeCmd(CMD17, 0xf, 0);

    uint8_t r1 = SD_readR1();

    int timeout=50;     // Based on observation
    uint8_t token;
    do {
        token = SPI_rw(0xff);
        timeout--;
    } while ( (token != TOKEN_SINGLE_BLOCK_START) && timeout);

    //flush data and CRC
    for (int j = 0; j < (512+2); j++) {
        SPI_rw(0xff);
    }

    SPI_CS_DISABLE();

    AU_ASSERT(r1 == R1_READY_STATE);
    AU_ASSERT(token == TOKEN_SINGLE_BLOCK_START);

    AU_UNIT_END;
}

int main (void) {

    AU_RUN_TEST(0x01, test_cmd17);

    AU_OUTPUT();

    return (0);
}
