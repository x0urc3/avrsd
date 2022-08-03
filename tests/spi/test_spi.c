#include "avrunit.h"
#include "spi_driver.h"

static int test_init(void) {
    AU_UNIT_START;

    SPI_init();
    AU_ASSERT(SPCR == 0b01010011);

    AU_UNIT_END;
}

static int test_rw(void) {
    AU_UNIT_START;

    int range = 5;
    int expr = 1;

    for (int i = 0;i < range;i++) {
        if (SPI_rw(0xff) == 0xff) {
            expr=0;
        }
    }

    AU_ASSERT(expr);

    AU_UNIT_END;
}

int main (void) {

    AU_RUN_TEST(0x01, test_init);
    AU_RUN_TEST(0x02, test_rw);

    AU_OUTPUT();

    return (0);
}
