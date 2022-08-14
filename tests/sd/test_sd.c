#include "avrunit.h"
#include "sd.h"

static int test_powerup(void) {
    AU_UNIT_START;

    SD_init();
    SD_powerUp();

#ifdef SD_PIN_VCC
    AU_ASSERT(SD_PORT & _BV(SD_PIN_VCC));
#endif // SD_PIN_VCC

    AU_ASSERT(SPI_PORT & _BV(SPI_PIN_CS));

    AU_UNIT_END;
}

static int test_cmd0(void) {
    AU_UNIT_START;

    uint8_t r1 =  SD_sendCmd(CMD0, 0);

    AU_ASSERT(r1 == 0);

    AU_UNIT_END;
}

static int test_cmd8(void) {
    AU_UNIT_START;

    uint32_t arg;
    arg = 0x1 << 8;    // VHS
    arg |= 0xaa;       // check pattern
    uint8_t r1 =  SD_sendCmd(CMD8, arg);

    AU_ASSERT(r1 == 0);

    AU_UNIT_END;
}


int main (void) {

    AU_RUN_TEST(0x01, test_powerup);
    AU_RUN_TEST(0x11, test_cmd0);
    AU_RUN_TEST(0x12, test_cmd8);

    AU_OUTPUT();

    return (0);
}
