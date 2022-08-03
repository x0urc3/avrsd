#include "avrunit.h"
#include "spi_driver.h"

static int test_init(void) {
    AU_UNIT_START;

    SPI_init();
    AU_ASSERT(SPCR == 0b01010011);

    AU_UNIT_END;
}

int main (void) {

    AU_RUN_TEST(0x0a, test_init);

    AU_OUTPUT();

    return (0);
}
