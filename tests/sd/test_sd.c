#include "avrunit.h"
#include "sd.h"

static int test_powerup(void) {
    AU_UNIT_START;

    SD_setup();
    SD_powerUp();

#ifdef SD_PIN_VCC
    AU_ASSERT(SD_PORT & _BV(SD_PIN_VCC));
#endif // SD_PIN_VCC

    AU_ASSERT(SPI_PORT & _BV(SPI_PIN_CS));

    AU_UNIT_END;
}

static int test_cmd0(void) {
    AU_UNIT_START;

    SPI_CS_ENABLE();
    SD_writeCmd(CMD0, 0, CMD0_CRC);
    uint8_t r1 = SD_readR1();
    SPI_CS_DISABLE();

    AU_ASSERT(r1 == R1_IDLE_STATE);

    AU_UNIT_END;
}

static int test_cmd8_v2(void) {
    AU_UNIT_START;

    SPI_CS_ENABLE();
    SD_writeCmd(CMD8, CMD8_ARG, CMD8_CRC);

    uint8_t r7[5];
    SD_readResponse(r7, sizeof(r7));

    SPI_CS_DISABLE();

    AU_ASSERT(r7[0] == R1_IDLE_STATE);
    AU_ASSERT(r7[3] == VHS_27_36);
    AU_ASSERT(r7[4] == CHECK_PATTERN);

    AU_UNIT_END;
}

static int test_cmd8_v1(void) {
    AU_UNIT_START;

    SPI_CS_ENABLE();
    SD_writeCmd(CMD8, CMD8_ARG, CMD8_CRC);

    uint8_t r7[5];
    SD_readResponse(r7, sizeof(r7));

    SPI_CS_DISABLE();

    AU_ASSERT_FAIL(r7[0] == R1_ILLEGAL_COMMAND);
    AU_ASSERT(r7[3] == VHS_27_36);
    AU_ASSERT(r7[4] == CHECK_PATTERN);

    AU_UNIT_END;
}

static int test_acmd41(void) {
    AU_UNIT_START;

    SPI_CS_ENABLE();

    uint8_t r1, i=20;
    do {
        SD_writeAcmd(ACMD41, ACMD41_ARG1, 0);
        r1 = SD_readR1();
        i--;
    } while ((r1 != R1_OK) && i);

    SPI_CS_DISABLE();

    AU_ASSERT(r1 == R1_OK);

    AU_UNIT_END;
}

static int test_init(void) {
    AU_UNIT_START;

    AU_ASSERT(SD_init() == 0);

    AU_UNIT_END;
}


int main (void) {

    AU_RUN_TEST(0x01, test_powerup);
    AU_RUN_TEST(0x11, test_cmd0);
    AU_RUN_TEST(0x12, test_cmd8_v2);
    AU_RUN_TEST(0x13, test_cmd8_v1);
    AU_RUN_TEST(0x14, test_acmd41);
    AU_RUN_TEST(0x21, test_init);

    AU_OUTPUT();

    return (0);
}
