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

static int test_cmd8_v1(void) {
    AU_UNIT_START;

    SPI_CS_ENABLE();
    SD_writeCmd(CMD8, CMD8_ARG, CMD8_CRC);
    uint8_t r1 = SD_readR1();
    SPI_CS_DISABLE();

    AU_ASSERT(r1 & R1_ILLEGAL_COMMAND);

    AU_UNIT_END;
}


int main (void) {

    AU_RUN_TEST(0x01, test_powerup);
    AU_RUN_TEST(0x11, test_cmd0);
    AU_RUN_TEST(0x12, test_cmd8_v1);

    AU_OUTPUT();

    return (0);
}
