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

    AU_ASSERT(r1 == R1_OK);
    AU_ASSERT(token == TOKEN_SINGLE_BLOCK_START);

    AU_UNIT_END;
}

static int test_cmd13 (void) {
//    USART_init();

    AU_UNIT_START;

    SPI_CS_ENABLE();

    uint8_t r2[2];
    SD_writeCmd(CMD13, 0, 0);
    SD_readResponse(r2, sizeof(r2));

    SPI_CS_DISABLE();

    AU_ASSERT(r2[0] == R1_OK);
    AU_ASSERT(r2[1] == 0);

    AU_UNIT_END;
//    au_wait_serial('r');
//    au_send_serial((uint8_t *)r2, sizeof(r2));
}

int main (void) {

    AU_RUN_TEST(0x01, test_cmd17);
    AU_RUN_TEST(0x02, test_cmd13);

    AU_OUTPUT();

    return (0);
}
