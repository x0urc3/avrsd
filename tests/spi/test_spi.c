#include "avrunit.h"
#include "spi.h"

static int test_init(void) {
    AU_UNIT_START;

//    AU_IGNORED(1 == 1);

    AU_UNIT_END;
}

int main (void) {

    AU_RUN_TEST(0x0a, test_init);

    AU_OUTPUT();

    return (0);
}
