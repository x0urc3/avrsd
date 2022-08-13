#include "avrunit.h"
#include "sd.h"

static int test_powerup(void) {
    AU_UNIT_START;

    SD_init();
    SD_powerUp();

#ifdef SD_PIN_VCC
    AU_ASSERT(SD_PORT & _BV(SD_PIN_VCC));
#endif // SD_PIN_VCC

    AU_UNIT_END;
}

int main (void) {

    AU_RUN_TEST(0x01, test_powerup);

    AU_OUTPUT();

    return (0);
}
