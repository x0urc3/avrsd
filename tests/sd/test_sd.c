#include "avrunit.h"
#include "sd.h"

static int test_powerup(void) {
    AU_UNIT_START;

    SD_init();
    SD_powerUp();

    AU_UNIT_END;
}

int main (void) {

    AU_RUN_TEST(0x01, test_powerup);

    AU_OUTPUT();

    return (0);
}
